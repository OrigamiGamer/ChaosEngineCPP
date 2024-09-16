#pragma once

#include "common.h"

namespace ChaosEngine {
    namespace PhysicsEngine {
        typedef basic_type::vec2<float> POINT;
        struct LINEAR_FUNCTION {
            float k;
            float b;
        };

        inline void get_linear_function(POINT p1, POINT p2, LINEAR_FUNCTION& out_linear_fn);
        inline void get_collision_point(LINEAR_FUNCTION& linear_fn1, LINEAR_FUNCTION& linear_fn2, POINT& out_point);

        class CollisionBox;
        class PhysicalSpace;
    }
}