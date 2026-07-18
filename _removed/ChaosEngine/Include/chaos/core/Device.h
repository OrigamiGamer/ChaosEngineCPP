#pragma once

#include "chaos/chaos.h"


namespace chaos {


    class Device : public Base {
    public:
        device::Engine* engine = nullptr;

        Device();

    };


}