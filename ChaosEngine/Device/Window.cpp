#pragma once

#include "Common.h"

namespace Chaos::Device {
    Window::Window(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);
        this->INIT("Window");
    }

    Window::~Window()
    {

    }

    void Window::initialize(WindowProperty* new_windowProp)
    {
        if (new_windowProp != nullptr) {
            new_windowProp;
        }
        else {
            // default window property
            
        }
    }
}