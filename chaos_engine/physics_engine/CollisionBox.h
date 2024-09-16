#pragma once

#include "common_physics_engine.h"

namespace ChaosEngine {
    namespace PhysicsEngine {
        class CollisionBox {
        public:
            std::vector<POINT> vec_vertex;
            CollisionBox();
        };
    }
}