#pragma once

#include "GraphicX/GraphicX.h"

namespace Chaos::GraphicX {



    RenderTaskParam_Line::RenderTaskParam_Line(vec2<float> pos1, vec2<float> pos2, float strokeWidth)
        : pos1(pos1), pos2(pos2), strokeWidth(strokeWidth)
    {

    }



    RenderTaskParam_Texture::RenderTaskParam_Texture(
        vec2<float> pos,
        Texture* texture,
        vec2<float> size,
        vec2<float> pivot,
        float rotation
    ) : pos(pos), texture(texture), size(size), pivot(pivot), rotation(rotation)
    {
        if (size.x == -1 && size.y == -1) this->size = texture->getSize();
    }



    RenderTask::RenderTask(RenderTaskType type, RenderTaskParam param, float order)
        : type(type), param(param), order(order)
    {

    }



    // Renderer



    Renderer::Renderer(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("Renderer");
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
        this->_hwndRenderTarget->CreateCompatibleRenderTarget(&this->_bitmapRenderTarget);

        // create a solid color brush
        hr = this->_bitmapRenderTarget->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::LightGreen, 1.0f),
            &this->_brush
        );
        if (FAILED(hr)) return false;

        CoUninitialize();
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
            texture.second.release();
        }
        this->_loadedTextures.clear();

        // release D2D devices
        System::safeReleaseCOM(this->_hwndRenderTarget);
        System::safeReleaseCOM(this->_bitmapRenderTarget);
        System::safeReleaseCOM(this->_brush);
        System::safeReleaseCOM(this->_d2dFactory);
        System::safeReleaseCOM(this->_wicFactory);
    }



    Texture* Renderer::loadTextureFromImageFile(std::wstring filename, std::string textureName)
    {
        IWICBitmapDecoder* decoder = nullptr;
        IWICBitmapFrameDecode* frameDecode = nullptr;
        IWICFormatConverter* converter = nullptr;

        // Load the image file
        HRESULT hr = this->_wicFactory->CreateDecoderFromFilename(
            System::locate(filename).c_str(),
            NULL,
            GENERIC_READ,
            WICDecodeMetadataCacheOnDemand,
            &decoder
        );
        if (FAILED(hr)) return nullptr;

        // Get the first frame of the image
        hr = decoder->GetFrame(0, &frameDecode);
        if (FAILED(hr)) return nullptr;;

        // Format convert to 32bppPBGRA
        hr = this->_wicFactory->CreateFormatConverter(&converter);
        if (FAILED(hr)) return nullptr;;

        hr = converter->Initialize(
            frameDecode,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            NULL,
            0.f,
            WICBitmapPaletteTypeCustom
        );
        if (FAILED(hr)) return nullptr;;

        // Create a d2d bitmap from the converted frame
        if (textureName == "" || textureName.empty()) textureName = System::wstringToString(System::getFileName(filename));

        auto _it = this->_loadedTextures.find(textureName);
        if (_it != this->_loadedTextures.end()) return nullptr; // texture already loaded
        else _it = this->_loadedTextures.insert(std::make_pair(textureName, Texture(new ID2D1Bitmap*))).first;
        /////////////// bug here, and it sourced from the double-layer pointer design of Texture.

        hr = this->_bitmapRenderTarget->CreateBitmapFromWicBitmap(
            converter,
            NULL,
            _it->second._bitmap
        );

        if (FAILED(hr)) {
            this->_loadedTextures.erase(_it);
            return nullptr;
        };

        // Release COM objects
        System::safeReleaseCOM(converter);
        System::safeReleaseCOM(frameDecode);
        System::safeReleaseCOM(decoder);

        return &_it->second;
    }



    Texture* Renderer::getLoadedTexture(std::string textureName)
    {
        return this->_loadedTextures.find(textureName) == this->_loadedTextures.end() ?
            nullptr : &this->_loadedTextures.at(textureName);
    }



    bool Renderer::createViewport(std::string viewportName, std::shared_ptr<GraphicX::Viewport>* out_viewport)
    {
        // use default name if empty
        if (viewportName == "") viewportName = "Viewport " + std::to_string(this->viewports.size() + 1);
        // check if viewport already exists
        for (auto& viewport : this->viewports) if (viewport->name == viewportName) return false;

        // create and initialize a new viewport
        this->viewports.resize(this->viewports.size() + 1);
        this->viewports.back().reset(new GraphicX::Viewport(this->engine));
        this->viewports.back()->SET_NAME(viewportName);

        // output the viewport created as parameter
        if (out_viewport) out_viewport->reset(this->viewports.back().get());
        return true;
    }



    inline bool Renderer::createViewport(std::shared_ptr<GraphicX::Viewport>& out_viewport)
    {
        return this->createViewport("", &out_viewport);
    }



    void Renderer::pushTask(RenderTask& new_task)
    {
        this->tasks.insert(
            std::lower_bound(
                this->tasks.begin(),
                this->tasks.end(),
                new_task,
                [](const RenderTask& a, const RenderTask& b) { return a.order < b.order; }
            ),
            new_task
        );
    }



    void Renderer::popTask()
    {
        this->tasks.pop_back();
    }



    void Renderer::beginDraw()
    {
        if (this->_bitmapRenderTarget) {
            this->_bitmapRenderTarget->BeginDraw();
            this->_bitmapRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
        }

    }



    void Renderer::endDraw()
    {
        // render graphics on world
        if (this->_bitmapRenderTarget) {
            for (auto& task : this->tasks) {
                switch (task.type) {

                case RenderTaskType::Line:
                    if (auto* param = std::get_if<RenderTaskParam_Line>(&task.param)) {
                        this->_bitmapRenderTarget->DrawLine(
                            { param->pos1.x, param->pos1.y },
                            { param->pos2.x, param->pos2.y },
                            this->_brush,
                            param->strokeWidth
                        );
                    }

                    break;
                case RenderTaskType::Texture:
                    if (auto* param = std::get_if<RenderTaskParam_Texture>(&task.param)) {
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
                                param->pivot.x,
                                param->pivot.y,
                                param->pivot.x + param->size.x,
                                param->pivot.y + param->size.y
                            )
                        );
                    }

                    break;
                default:
                    // ...
                    break;
                }
            }
            this->_bitmapRenderTarget->EndDraw();
        }
        this->tasks.clear();

        // render viewports to world
        if (this->_bitmapRenderTarget) {
            this->_hwndRenderTarget->BeginDraw();
            this->_hwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
            for (auto& viewport : this->viewports) {
                // look the bug here, your texture handles a double-layer pointer.
                // when dev using a new Texture, the first is a nullptr initially.
                // so if the second is accessed now, it will must be an error. So the second must be accessed.
                this->_bitmapRenderTarget->GetBitmap(&viewport->_bitmap);

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



}