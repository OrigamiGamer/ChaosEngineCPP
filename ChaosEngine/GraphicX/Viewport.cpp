#pragma once

#include "GraphicX/GraphicX.h"

namespace Chaos::GraphicX {



    Viewport::Viewport(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("Viewport");

    }



    void Viewport::release()
    {
        System::safeReleaseCOM(this->_bitmap);

    }



}