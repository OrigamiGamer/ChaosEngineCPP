#pragma once

#include "ChaosEngine.h"

namespace Chaos::GameObject {



    class Actor : public Base {
    public:
        Actor(InternalDevice::Engine* new_engine);
        ~Actor();

    };



}