#pragma once

#include "Common.h"

namespace Chaos::Graphic {
    Renderer::Renderer(Device::Engine* new_engine)
    {
        this->engine = new_engine;
    }

    Renderer::~Renderer()
    {
        // release graphic api
    }
}