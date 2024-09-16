#pragma once

#include "common_physics_engine.h"

namespace ChaosEngine {
    namespace PhysicsEngine {
        inline void get_linear_function(basic_type::vec2<float> p1, basic_type::vec2<float> p2, LINEAR_FUNCTION& out_linear_fn) {
            out_linear_fn.k = (p2.y - p1.y) / (p2.x - p1.x);
            out_linear_fn.b = p1.y - out_linear_fn.k * p1.x;
        }
        inline void get_collision_point(LINEAR_FUNCTION& linear_fn1, LINEAR_FUNCTION& linear_fn2, basic_type::vec2<float>& out_point) {
            out_point.x = (linear_fn2.b - linear_fn1.b) / (linear_fn1.k - linear_fn2.k);
            out_point.y = linear_fn1.k * out_point.x + linear_fn1.b;
        }
    }
}