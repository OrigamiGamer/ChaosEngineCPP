#pragma once

#include "Common.h"

namespace Chaos::Device {
    Window::Window(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);
        this->INIT("Window");
        this->_glfwWindow = nullptr;
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
            this->_glfwWindow = glfwCreateWindow(
                new_windowProp->size.x,
                new_windowProp->size.y,
                new_windowProp->title.c_str(),
                nullptr,
                nullptr
            );
        }
    }
}