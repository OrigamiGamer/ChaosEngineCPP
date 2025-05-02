#pragma once

#include "Common.h"

namespace Chaos::Graphic {

    RenderTaskParam_Line::RenderTaskParam_Line(vec2<float> pos1, vec2<float> pos2, float strokeWidth)
        : pos1(pos1), pos2(pos2), strokeWidth(strokeWidth)
    {

    }

    RenderTask::RenderTask(unsigned int type, RenderTaskParam param)
        : type(type), param(param)
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

        // create D2D factory
        HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->_d2dFactory);
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
            D2D1::ColorF(D2D1::ColorF::LightGreen),
            &this->_brush
        );
        if (FAILED(hr)) return false;

        return true;
    }

    inline bool Renderer::initialize(Device::Window& new_window)
    {
        return this->initialize(&new_window);
    }

    Graphic::Texture* Renderer::loadTextureFromFile(std::wstring filename)
    {
        IWICBitmapDecoder* decoder = nullptr;
        IWICBitmapFrameDecode* frameDecode = nullptr;
        IWICFormatConverter* converter = nullptr;

        // Load the image file
        HRESULT hr = _wicFactory->CreateDecoderFromFilename(
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
        hr = _wicFactory->CreateFormatConverter(&converter);
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

        // Create a bitmap from the converted frame
        this->textures.resize(this->textures.size() + 1);
        hr = this->_renderTarget->CreateBitmapFromWicBitmap(
            converter,
            &this->textures.back()->_bitmap
        );
        if (FAILED(hr)) return nullptr;

        // Release COM objects
        System::safeReleaseCOM(converter);
        System::safeReleaseCOM(frameDecode);
        System::safeReleaseCOM(decoder);

        return this->textures.back();
    }

    void Renderer::pushTask(RenderTask& new_task)
    {
        this->tasks.push_back(new_task);
    }

    void Renderer::popTask(RenderTask* new_task)
    {
        if (new_task != nullptr) this->tasks.pop_back();
    }

    void Renderer::beginDraw()
    {
        if (this->_renderTarget != nullptr) {
            this->_renderTarget->BeginDraw();
            this->_renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkGray));
        }

    }

    void Renderer::endDraw()
    {
        if (this->_renderTarget != nullptr) {
            this->_renderTarget->EndDraw();

            for (auto& task : this->tasks) {
                switch (task.type) {

                case RenderTaskType::Line:  // Line
                    if (const auto* param = std::get_if<RenderTaskParam_Line>(&task.param)) {
                        this->_renderTarget->DrawLine(
                            { param->pos1.x, param->pos1.y },
                            { param->pos2.x, param->pos2.y },
                            this->_brush,
                            param->strokeWidth
                        );
                    }
                    break;
                }

            }
        }
        this->tasks.clear();
    }

}