#pragma once

#include "Common.h"

namespace Chaos::Graphic {
    Renderer::Renderer()
    {
        engine = nullptr;
    }

    Renderer::~Renderer()
    {
        // release graphic api
    }
}