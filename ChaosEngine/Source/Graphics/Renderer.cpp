#pragma once

#include "Class/Graphics/Graphics.h"

namespace Chaos::Graphics {



    // RenderTask

    RenderTask::RenderTask(RenderTaskType type, RenderTaskParam param, float order)
        : type(type), param(param), order(order)
    {

    }



    // Renderer

    Renderer::Renderer()
    {
        this->INIT("Renderer");
        this->SET_NAME("renderer_" + std::to_string(GraphicManager::s_renderers.size() + 1));
    }



    bool Renderer::initialize(WindowX::Window* new_window)
    {
        HWND hwnd = glfwGetWin32Window(new_window->_glfwWindow);
        HRESULT hr = CoInitialize(NULL);


        // create D2D factory
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->_d2dFactory);
        if (FAILED(hr)) return false;


        // create WIC factory
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&this->_wicFactory)
        );
        if (FAILED(hr)) return false;


        // create RenderTargets
        if (!this->_d2dFactory) return false;
        RECT rect;
        GetClientRect(hwnd, &rect);
        Chaos::vec2<LONG> size = { rect.right - rect.left, rect.bottom - rect.top };


        // create hwnd render target
        hr = _d2dFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(
                D2D1_RENDER_TARGET_TYPE_HARDWARE
            ),
            D2D1::HwndRenderTargetProperties(
                hwnd,
                D2D1::SizeU(size.x, size.y)
            ),
            &this->_hwndRenderTarget
        );
        if (FAILED(hr)) return false;


        // create bitmap render target
        this->_hwndRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(1000, 1000), &this->_bitmapRenderTarget);


        // create two solid color brushs
        hr = this->_bitmapRenderTarget->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::LightPink, 1.0f),
            &this->_brush
        );
        if (FAILED(hr)) return false;

        hr = this->_bitmapRenderTarget->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::LightPink, 1.0f),
            &this->_fillingBrush
        );
        if (FAILED(hr)) return false;

        // register this renderer to Graphics manager
        GraphicManager::registerRenderer(this);

        // initialize renderer property
        _hwndRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
        _bitmapRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED); // WTF, so how to disable the antialias mode?

        return true;
    }



    inline bool Renderer::initialize(WindowX::Window& new_window)
    {
        return this->initialize(&new_window);
    }



    void Renderer::release()
    {
        // release textures
        for (auto& texture : this->_loadedTextures) {
            texture->release();
            delete texture;
        }
        this->_loadedTextures.clear();


        // release viewports
        for (auto& viewport : this->viewports) {
            viewport.second->release();
        }


        // release D2D devices
        System::safeReleaseCOM(this->_hwndRenderTarget);
        System::safeReleaseCOM(this->_bitmapRenderTarget);
        System::safeReleaseCOM(this->_brush);
        System::safeReleaseCOM(this->_wicFactory);
        System::safeReleaseCOM(this->_d2dFactory);
        CoUninitialize();


        Log::OutputStream _out("INFO");
        _out.push("Renderer -> release()");
        this->_logger.print(_out);

    }



    Texture* Renderer::loadTextureFromImageFile(std::string filename, std::string new_textureName)
    {
        IWICBitmapDecoder* decoder = nullptr;
        IWICBitmapFrameDecode* frameDecode = nullptr;
        IWICFormatConverter* converter = nullptr;


        // load the image file to decoder
        HRESULT hr = this->_wicFactory->CreateDecoderFromFilename(
            System::stringToWstring(System::locate(filename)).c_str(),  // WARNING: string to wstring
            NULL,
            GENERIC_READ,
            WICDecodeMetadataCacheOnDemand,
            &decoder
        );


        // get the first frame of the image
        if (SUCCEEDED(hr)) hr = decoder->GetFrame(0, &frameDecode);


        // format convert to 32bppPBGRA
        if (SUCCEEDED(hr)) hr = this->_wicFactory->CreateFormatConverter(&converter);

        if (SUCCEEDED(hr)) hr = converter->Initialize(
            frameDecode,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            NULL,
            0.f,
            WICBitmapPaletteTypeCustom
        );


        // create a texture resource from a d2d bitmap
        Texture* _resultTexture = nullptr;
        if (SUCCEEDED(hr)) {
            if (new_textureName == "" || new_textureName.empty()) new_textureName = System::getFileName(filename);

            if (!this->getLoadedTexture(new_textureName)) {
                this->_loadedTextures.push_back(new Texture(new ID2D1Bitmap*));
                _resultTexture = this->_loadedTextures.back();
                _resultTexture->_bitmap;

                // create a d2d bitmap from the converted frame
                hr = this->_bitmapRenderTarget->CreateBitmapFromWicBitmap(
                    converter,
                    NULL,
                    _resultTexture->_bitmap
                );

                if (SUCCEEDED(hr)) {
                    _resultTexture->SET_NAME(new_textureName);
                    std::cout << "Renderer -> loaded texture -> " << _resultTexture->nameId << std::endl;
                }
                else {  // failed to create d2d-bitmap from wic-bitmap
                    _resultTexture = nullptr;
                    this->_loadedTextures.pop_back();
                }
            }
        }


        // release COM objects
        System::safeReleaseCOM(converter);
        System::safeReleaseCOM(frameDecode);
        System::safeReleaseCOM(decoder);

        return _resultTexture; // nullptr: the texture had already been loaded
    }



    Texture* Renderer::getLoadedTexture(std::string textureName)
    {
        for (auto& texture : this->_loadedTextures)
            if (texture->nameId == textureName)
                return texture;
        return nullptr;
    }



    bool Renderer::registerViewport(Graphics::Viewport* new_viewport, std::string viewportName)
    {
        // use default name if empty
        if (viewportName == "") viewportName = "Viewport " + std::to_string(this->viewports.size() + 1);
        // check if viewport already exists
        for (auto& viewport : this->viewports) if (viewport.second->nameId == viewportName) return false;

        // initialize the new viewport and register it into this renderer
        new_viewport->renderer = this;
        new_viewport->SET_NAME(viewportName);
        this->viewports.insert(std::make_pair(viewportName, new_viewport));

        return true;
    }



    bool Renderer::registerViewport(Graphics::Viewport& new_viewport, std::string viewportName)
    {
        return this->registerViewport(&new_viewport);
    }



    void Renderer::SetCanvasSize(vec2<float> new_size)
    {
        System::safeReleaseCOM(this->_bitmapRenderTarget);
        this->_hwndRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(new_size.x, new_size.y), &this->_bitmapRenderTarget);
    }



    void Renderer::SetCanvasSize(float x, float y)
    {
        this->SetCanvasSize({ x,y });
    }



    inline vec2<float> Renderer::getCanvasSize() const
    {
        D2D1_SIZE_F _size = this->_bitmapRenderTarget->GetSize();
        return vec2<float>(_size.width, _size.height);
    }



    inline vec2<float> Renderer::getMaximumCanvasSize() const
    {
        const auto _max_size = this->_hwndRenderTarget->GetMaximumBitmapSize();
        return vec2<float>(_max_size, _max_size);
    }



    void Renderer::SetBrushColor(Color new_brushColor, Color new_fillingBrushColor)
    {
        this->_brush->SetColor(D2D1::ColorF(new_brushColor.r, new_brushColor.g, new_brushColor.b));

        if (new_fillingBrushColor.r != -1 && new_fillingBrushColor.g != -1 && new_fillingBrushColor.b != -1)
            this->_fillingBrush->SetColor(D2D1::ColorF(new_fillingBrushColor.r, new_fillingBrushColor.g, new_fillingBrushColor.b));
    }



    void Renderer::pushTask(RenderTask& new_task)
    {
        this->_tasks.insert(
            std::lower_bound(
                this->_tasks.begin(),
                this->_tasks.end(),
                new_task,
                [](const RenderTask& a, const RenderTask& b) { return a.order < b.order; }
            ),
            new_task
        );
    }



    void Renderer::popTask()
    {
        this->_tasks.pop_back();
    }



    void Renderer::_pushTransform(vec2<float> pivot, float rotation, vec2<float> scale)
    {
        D2D1_MATRIX_3X2_F _matrix, _matrix_rotation, _matrix_scale;
        _matrix_rotation = D2D1::Matrix3x2F::Rotation(rotation, D2D1::Point2F(pivot.x, pivot.y));
        _matrix_scale = D2D1::Matrix3x2F::Scale(scale.x, scale.y, D2D1::Point2F(pivot.x, pivot.y));
        _matrix = _matrix_rotation * _matrix_scale;

        if (this->_transformMatrixes.size() > 0)
            _matrix = this->_transformMatrixes.back() * _matrix;    // last * new

        this->_bitmapRenderTarget->SetTransform(_matrix);
        this->_transformMatrixes.push_back(_matrix);
    }



    void Renderer::_popTransform()
    {
        this->_transformMatrixes.pop_back();
        if (this->_transformMatrixes.size() > 0)
            this->_bitmapRenderTarget->SetTransform(this->_transformMatrixes.back());
        else
            this->_bitmapRenderTarget->SetTransform(D2D1::Matrix3x2F());
    }



    void Renderer::_render()
    {
        // render the Graphicss on game world
        if (this->_bitmapRenderTarget) {
            this->_bitmapRenderTarget->BeginDraw();
            this->_bitmapRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

            for (auto& task : this->_tasks) {
                switch (task.type) {

                case RenderTaskType::Line:
                    if (auto* param = std::get_if<RenderTaskParam_Line>(&task.param)) {
                        this->_pushTransform(param->pivot, param->rotation, param->scale);

                        this->_bitmapRenderTarget->DrawLine(
                            { param->pos1.x, param->pos1.y },
                            { param->pos2.x, param->pos2.y },
                            this->_brush,
                            param->strokeWidth,
                            nullptr
                        );

                        this->_popTransform();
                    }

                    break;
                case RenderTaskType::Rectangle:
                    if (auto* param = std::get_if<RenderTaskParam_Rectangle>(&task.param)) {
                        this->_pushTransform(param->pivot, param->rotation, param->scale);

                        D2D1_RECT_F _rect = D2D1::RectF(
                            param->pos.x,
                            param->pos.y,
                            param->pos.x + param->size.x,
                            param->pos.y + param->size.y
                        );

                        if (param->radius.x == 0 && param->radius.y == 0) {
                            // rectangle
                            this->_bitmapRenderTarget->DrawRectangle(
                                _rect,
                                this->_brush,
                                param->strokeWidth,
                                nullptr
                            );
                            // fill
                            if (param->isFilled) {
                                this->_bitmapRenderTarget->FillRectangle(
                                    _rect,
                                    this->_fillingBrush
                                );
                            }
                        }
                        else {
                            // rounded rectangle
                            D2D1_ROUNDED_RECT _roundedRect = D2D1::RoundedRect(
                                _rect,
                                param->radius.x,
                                param->radius.y
                            );
                            this->_bitmapRenderTarget->DrawRoundedRectangle(
                                _roundedRect,
                                this->_brush,
                                param->strokeWidth,
                                nullptr
                            );
                            // fill
                            if (param->isFilled) {
                                this->_bitmapRenderTarget->FillRoundedRectangle(
                                    _roundedRect,
                                    this->_fillingBrush
                                );
                            }
                        }

                        this->_popTransform();
                    }

                    break;
                case RenderTaskType::Ellipse:
                    if (auto* param = std::get_if<RenderTaskParam_Ellipse>(&task.param)) {
                        this->_pushTransform(param->pivot, param->rotation, param->scale);

                        // ellipse
                        D2D1_ELLIPSE _ellipse = D2D1::Ellipse(
                            D2D1::Point2F(
                                param->pos.x,
                                param->pos.y
                            ),
                            param->radius.x,
                            param->radius.y
                        );
                        this->_bitmapRenderTarget->DrawEllipse(
                            _ellipse,
                            this->_brush,
                            param->strokeWidth,
                            nullptr
                        );
                        // fill
                        if (param->isFilled) {
                            this->_bitmapRenderTarget->FillEllipse(
                                _ellipse,
                                this->_fillingBrush
                            );
                        }

                        this->_popTransform();
                    }

                    break;
                case RenderTaskType::Texture:
                    if (auto* param = std::get_if<RenderTaskParam_Texture>(&task.param)) {
                        this->_pushTransform(param->pivot, param->rotation, param->scale);

                        if (!param->texture) break;
                        if (!param->texture->_bitmap) break;
                        this->_bitmapRenderTarget->DrawBitmap(
                            *param->texture->_bitmap,
                            D2D1::RectF(
                                param->pos.x,
                                param->pos.y,
                                param->pos.x + param->size.x,
                                param->pos.y + param->size.y
                            ),
                            param->opacity,
                            D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
                            D2D1::RectF(
                                param->texturePos.x,
                                param->texturePos.y,
                                param->texturePos.x + param->textureSize.x,
                                param->texturePos.y + param->textureSize.y
                            )
                        );

                        this->_popTransform();
                    }

                    break;
                default:
                    // ...

                    break;
                }
            }
            this->_bitmapRenderTarget->EndDraw();
        }
        this->_tasks.clear();

        // render the viewports to game world on window
        if (this->_bitmapRenderTarget) {
            this->_hwndRenderTarget->BeginDraw();
            this->_hwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
            for (auto& it : this->viewports) {
                auto& viewport = it.second;
                this->_bitmapRenderTarget->GetBitmap(&viewport->_bitmap);
                if (!viewport->_bitmap) break;

                // fix viewport.viewPos gets out of range of the game world
                vec2<float> rect_lt = viewport->viewPos;
                vec2<float> rect_rb = viewport->viewPos + viewport->viewSize;
                D2D1_SIZE_F _texSize = viewport->_bitmap->GetSize();
                if (rect_lt.x < 0) viewport->viewPos.x = 0;
                if (rect_lt.y < 0) viewport->viewPos.y = 0;
                if (rect_rb.x > _texSize.width) viewport->viewPos.x = _texSize.width - viewport->viewSize.x;
                if (rect_rb.y > _texSize.height) viewport->viewPos.y = _texSize.height - viewport->viewSize.y;

                this->_hwndRenderTarget->DrawBitmap(
                    viewport->_bitmap,
                    D2D1::RectF(
                        viewport->pos.x,
                        viewport->pos.y,
                        viewport->pos.x + viewport->size.x,
                        viewport->pos.y + viewport->size.y
                    ),
                    1.0f,
                    D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
                    D2D1::RectF(
                        viewport->viewPos.x,
                        viewport->viewPos.y,
                        viewport->viewPos.x + viewport->viewSize.x,
                        viewport->viewPos.y + viewport->viewSize.y
                    )
                );

                viewport->release();
            }
            this->_hwndRenderTarget->EndDraw();
        }

    }



    void Renderer::_resizeWindow(vec2<int> new_size)
    {
        if (this->_hwndRenderTarget) this->_hwndRenderTarget->Resize(D2D1::SizeU(new_size.x, new_size.y));
    }



}