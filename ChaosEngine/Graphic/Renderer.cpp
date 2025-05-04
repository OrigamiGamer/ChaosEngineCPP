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

        // create HwndRenderTarget
        if (!this->_d2dFactory) return false;
        RECT rect;
        GetClientRect(hwnd, &rect);
        hr = _d2dFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(
                D2D1_RENDER_TARGET_TYPE_HARDWARE
            ),
            D2D1::HwndRenderTargetProperties(
                hwnd,
                { (UINT)(rect.right - rect.left),(UINT)(rect.bottom - rect.top) }
            ),
            &this->_renderTarget
        );
        if (FAILED(hr)) return false;

        // create a solid color brush
        hr = this->_renderTarget->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::Red, 1.0f),
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
        this->textures.resize(this->textures.size() + 1);
        hr = this->_renderTarget->CreateBitmapFromWicBitmap(
            converter,
            NULL,
            &this->textures.back()._bitmap
        );
        if (FAILED(hr)) {
            this->textures.pop_back();
            return nullptr;
        };

        // Release COM objects
        System::safeReleaseCOM(converter);
        System::safeReleaseCOM(frameDecode);
        System::safeReleaseCOM(decoder);

        return &this->textures.back();
    }

    void Renderer::pushTask(RenderTask& new_task)
    {
        // binary insert, sort by order
        // this->tasks.push_back(new_task);
        this->tasks.insert(
            std::lower_bound(
                this->tasks.begin(),
                this->tasks.end(),
                new_task, [](const RenderTask& a, const RenderTask& b) { return a.order < b.order; }
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
        if (this->_renderTarget != nullptr) {
            this->_renderTarget->BeginDraw();
            this->_renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
        }

    }

    void Renderer::endDraw()
    {
        if (this->_renderTarget != nullptr) {
            for (auto& task : this->tasks) {
                switch (task.type) {

                case RenderTaskType::Line:
                    if (auto* param = std::get_if<RenderTaskParam_Line>(&task.param)) {
                        this->_renderTarget->DrawLine(
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
                        this->_renderTarget->DrawBitmap(
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
            this->_renderTarget->EndDraw();
        }
        this->tasks.clear();
    }

}