#pragma once

#include "Common.h"

namespace Chaos::Device {
    Window::Window(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);
    }

    Window::~Window()
    {

    }
}