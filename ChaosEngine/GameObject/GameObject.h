#pragma once

#include "ChaosEngine.h"

namespace Chaos::GameObject {



    class Actor : public Base {
    public:
        InternalDevice::Scene* scene = nullptr;

        Actor();

        ~Actor();

        // ...

    };



}