#pragma once

#include "GraphicX/GraphicX.h"

namespace Chaos::Graphic {



    Viewport::Viewport(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("Viewport");

    }



    Viewport::~Viewport()
    {

    }


    
}