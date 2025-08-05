#pragma once

#include "GraphicX/GraphicX.h"

namespace Chaos::GraphicX {



    Viewport::Viewport()
    {
        this->INIT("Viewport");

    }



    void Viewport::release()
    {
        System::safeReleaseCOM(this->_bitmap);

    }


    
}