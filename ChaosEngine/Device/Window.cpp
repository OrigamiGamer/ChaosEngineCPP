#pragma once

#include "Common.h"

namespace Chaos::Device {
    Window::Window(Device::Engine* new_engine)
    {
        this->engine = new_engine;
    }

    Window::~Window()
    {

    }
}