#pragma once

#include "Common.h"

namespace Chaos::Graphic {

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

    Renderer::Renderer(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);
        this->INIT("Renderer");
    }

    Renderer::~Renderer()
    {

    }

    bool Renderer::initialize(Device::Window* new_window)
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

    inline bool Renderer::initialize(Device::Window& new_window)
    {
        return this->initialize(&new_window);
    }

    Texture* Renderer::loadTextureFromFile(std::wstring filename)
    {
        IWICBitmapDecoder* decoder = nullptr;
        IWICBitmapFrameDecode* frameDecode = nullptr;
        IWICFormatConverter* converter = nullptr;

        std::wstring tempstr = System::locate(filename);

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
        this->loadedTextures.resize(this->loadedTextures.size() + 1);
        hr = this->_bitmapRenderTarget->CreateBitmapFromWicBitmap(
            converter,
            NULL,
            &this->loadedTextures.back()._bitmap
        );
        if (FAILED(hr)) {
            this->loadedTextures.pop_back();
            return nullptr;
        };

        // Release COM objects
        System::safeReleaseCOM(converter);
        System::safeReleaseCOM(frameDecode);
        System::safeReleaseCOM(decoder);

        return &this->loadedTextures.back();
    }

    bool Renderer::createViewport(std::string viewportName, Chaos::shared_ptr<Graphic::Viewport>* out_viewport)
    {
        // use default name if empty
        if (viewportName == "") viewportName = "Viewport " + std::to_string(this->viewports.size() + 1);
        // check if viewport already exists
        for (auto& viewport : this->viewports) if (viewport->name == viewportName) return false;

        // create and initialize a new viewport
        this->viewports.resize(this->viewports.size() + 1);
        this->viewports.back().set(new Graphic::Viewport(this->engine.get()));
        this->viewports.back()->SET_NAME(viewportName);

        // output the viewport created as parameter
        if (out_viewport) out_viewport->refer(this->viewports.back().get());
        return true;
    }

    inline bool Renderer::createViewport(Chaos::shared_ptr<Graphic::Viewport>& out_viewport)
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
        // rebder world
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
                        this->_bitmapRenderTarget->DrawBitmap(
                            param->texture->_bitmap,
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
                    break;
                }
            }
            this->_bitmapRenderTarget->EndDraw();
        }
        this->tasks.clear();

        // render viewports
        if (this->_bitmapRenderTarget) {
            this->_hwndRenderTarget->BeginDraw();
            this->_hwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
            for (auto& viewport : this->viewports) {
                this->_bitmapRenderTarget->GetBitmap(&viewport->texture._bitmap);

                this->_hwndRenderTarget->DrawBitmap(
                    viewport->texture._bitmap,
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

            }
            this->_hwndRenderTarget->EndDraw();
        }
    }

}