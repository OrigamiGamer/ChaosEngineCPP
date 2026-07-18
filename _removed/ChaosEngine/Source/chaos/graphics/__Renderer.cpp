#include "chaos/graphics/Renderer.h"

namespace chaos::graphics {



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

        this->_logger.addType("SUCCESS", log::LevelColor::Green);

    }



    bool Renderer::initialize(windows::Window* in_window)
    {
        HWND hwnd = glfwGetWin32Window(in_window->_glfwWindow);
        HRESULT hr = CoInitialize(NULL);


        // create D2D factory
        D2D1_FACTORY_OPTIONS options;
#ifdef CHAOS_DEBUG
        options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#else
        options.debugLevel = D2D1_DEBUG_LEVEL_NONE;
#endif
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options, &this->_d2dFactory);
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
        chaos::vec2<LONG> size = { rect.right - rect.left, rect.bottom - rect.top };


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
            &this->_fillBrush
        );
        if (FAILED(hr)) return false;

        // register this renderer to Graphics manager
        GraphicManager::registerRenderer(this);

        // initialize renderer property
        _hwndRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
        _bitmapRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED); // WTF, it's useless, so how to disable the antialias mode?

        return true;
    }



    inline bool Renderer::initialize(windows::Window& in_window)
    {
        return this->initialize(&in_window);
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


        // // release canvases
        // for (auto& canvas : this->_canvases) {
        //     canvas.release();
        // }


        // release D2D devices
        system::SafeReleaseCOM(this->_hwndRenderTarget);
        system::SafeReleaseCOM(this->_bitmapRenderTarget);
        system::SafeReleaseCOM(this->_brush);
        system::SafeReleaseCOM(this->_wicFactory);
        system::SafeReleaseCOM(this->_d2dFactory);
        CoUninitialize();


        log::OutputStream _out("INFO");
        _out.push("Renderer -> release()");
        this->_logger.print(_out);

    }



    Texture* Renderer::loadTextureFromImageFile(std::string filename, std::string in_textureName)
    {
        IWICBitmapDecoder* decoder = nullptr;
        IWICBitmapFrameDecode* frameDecode = nullptr;
        IWICFormatConverter* converter = nullptr;


        // load the image file to decoder
        HRESULT hr = this->_wicFactory->CreateDecoderFromFilename(
            system::StringToWstring(system::Locate(filename)).c_str(),  // WARNING: string to wstring
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
            if (in_textureName == "" || in_textureName.empty()) in_textureName = system::GetFileName(filename);

            if (!this->getLoadedTexture(in_textureName)) {
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
                    _resultTexture->SET_NAME(in_textureName);

                    log::OutputStream _out;
                    _out.typeName = "SUCCESS";
                    _out.push("Renderer -> loaded texture -> \"");
                    _out.push(_resultTexture->nameId);
                    _out.push("\"");
                    this->_logger.print(_out);
                }
                else {  // failed to create d2d-bitmap from wic-bitmap
                    _resultTexture = nullptr;
                    this->_loadedTextures.pop_back();
                }
            }
        }


        // release COM objects
        system::SafeReleaseCOM(converter);
        system::SafeReleaseCOM(frameDecode);
        system::SafeReleaseCOM(decoder);

        return _resultTexture; // nullptr: the texture had already been loaded
    }



    Texture* Renderer::getLoadedTexture(std::string textureName)
    {
        for (auto& texture : this->_loadedTextures)
            if (texture->nameId == textureName)
                return texture;
        return nullptr;
    }



    bool Renderer::registerViewport(graphics::Viewport* in_viewport, std::string viewportName)
    {
        // use default name if empty
        if (viewportName == "") viewportName = "Viewport " + std::to_string(this->viewports.size() + 1);
        // check if viewport already exists
        for (auto& viewport : this->viewports) if (viewport.second->nameId == viewportName) return false;

        // initialize the new viewport and register it into this renderer
        in_viewport->renderer = this;
        in_viewport->SET_NAME(viewportName);
        this->viewports.insert(std::make_pair(viewportName, in_viewport));

        return true;
    }



    bool Renderer::registerViewport(graphics::Viewport& in_viewport, std::string viewportName)
    {
        return this->registerViewport(&in_viewport);
    }



    void Renderer::SetCanvasSize(vec2<float> in_size)
    {
        system::SafeReleaseCOM(this->_bitmapRenderTarget);
        this->_hwndRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(in_size.x, in_size.y), &this->_bitmapRenderTarget);
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



    void Renderer::SetBrushColor(Color in_brushColor, Color in_fillingBrushColor)
    {
        this->_brush->SetColor(D2D1::ColorF(in_brushColor.r, in_brushColor.g, in_brushColor.b));

        if (in_fillingBrushColor.r != -1 && in_fillingBrushColor.g != -1 && in_fillingBrushColor.b != -1)
            this->_fillBrush->SetColor(D2D1::ColorF(in_fillingBrushColor.r, in_fillingBrushColor.g, in_fillingBrushColor.b));
    }



    void Renderer::pushTask(RenderTask& in_task)
    {
        this->_tasks.insert(
            std::lower_bound(
                this->_tasks.begin(),
                this->_tasks.end(),
                in_task,
                [](const RenderTask& a, const RenderTask& b) { return a.order < b.order; }
            ),
            in_task
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

        if (this->_transformMatrixHeap.size() > 0)
            _matrix = this->_transformMatrixHeap.back() * _matrix;    // last * new

        this->_bitmapRenderTarget->SetTransform(_matrix);
        this->_transformMatrixHeap.push_back(_matrix);
    }



    void Renderer::_popTransform()
    {
        this->_transformMatrixHeap.pop_back();
        if (this->_transformMatrixHeap.size() > 0)
            this->_bitmapRenderTarget->SetTransform(this->_transformMatrixHeap.back());
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
                                    this->_fillBrush
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
                                    this->_fillBrush
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
                                this->_fillBrush
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



    void Renderer::_resizeWindow(vec2<int> in_size)
    {
        if (this->_hwndRenderTarget) this->_hwndRenderTarget->Resize(D2D1::SizeU(in_size.x, in_size.y));
    }



}