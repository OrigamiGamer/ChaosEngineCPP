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
        if (this->_glfwWindow != nullptr) glfwDestroyWindow(this->_glfwWindow);
    }

    bool Window::initialize(WindowProperty* new_windowProp)
    {
        if (new_windowProp != nullptr) {
            // User's window property
            this->_glfwWindow = glfwCreateWindow(
                new_windowProp->size.x,
                new_windowProp->size.y,
                new_windowProp->title.c_str(),
                nullptr,
                nullptr
            );
            if (!this->_glfwWindow) return false;
            glfwSetWindowPos(
                this->_glfwWindow,
                new_windowProp->pos.x,
                new_windowProp->pos.y
            );
        }
        else {
            // Default window property
            this->_glfwWindow = glfwCreateWindow(
                800,
                600,
                "Window",
                nullptr,
                nullptr
            );
            if (!this->_glfwWindow) return false;
        }
        return true;
    }
}