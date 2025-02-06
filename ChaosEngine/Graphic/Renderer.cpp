#pragma once

#include "Common.h"

namespace Chaos::Graphic {
    Renderer::Renderer(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);
        this->INIT("Renderer");
    }

    Renderer::~Renderer()
    {
        // release graphic api
    }
}