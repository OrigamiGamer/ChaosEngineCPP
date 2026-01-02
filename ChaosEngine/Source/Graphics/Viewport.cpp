#pragma once

#include "Class/Graphics/Graphics.h"

namespace Chaos::Graphics {



    Viewport::Viewport()
    {
        this->INIT("Viewport");

    }



    void Viewport::release()
    {
        System::safeReleaseCOM(this->_bitmap);

    }


    
}