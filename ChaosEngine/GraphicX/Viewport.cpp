#pragma once

#include "GraphicX/GraphicX.h"

namespace Chaos::GraphicX {



    Viewport::Viewport(Renderer* new_renderer)
    {
        this->renderer = new_renderer;
        this->INIT("Viewport");

    }



    void Viewport::release()
    {
        System::safeReleaseCOM(this->_bitmap);

    }



}