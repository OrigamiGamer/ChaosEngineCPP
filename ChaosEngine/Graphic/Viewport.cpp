#pragma once

#include "Common.h"

namespace Chaos::Graphic {

    Viewport::Viewport(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);
        this->INIT("Viewport");

    }

    Viewport::~Viewport()
    {
        std::cout << "[CALL] " << "Viewport -> ~Viewport()" << std::endl;
    }

}