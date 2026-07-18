#include "chaos/graphics/Viewport.h"

namespace chaos::graphics {



    Viewport::Viewport()
    {
        this->INIT("Viewport");

    }



    void Viewport::release()
    {
        system::SafeReleaseCOM(this->_bitmap);

    }


    
}