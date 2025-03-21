#pragma once

#include "Common.h"

namespace Chaos::Graphic {
    Renderer::Renderer(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);
        this->INIT("Renderer");
    }

    bool Renderer::initialize(Device::Window& new_window)
    {
        HWND hwnd = glfwGetWin32Window(new_window._glfwWindow);

        HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->_d2dFactory);
        if (FAILED(hr)) return false;

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

        return true;
    }

    Renderer::~Renderer()
    {

    }
}