#pragma once

#include "chaos/physics/physics.h"


namespace chaos::physics {



    class PhysicsEngine : public Device {
    public:

        PhysicsEngine();

        void update();

    };



}
