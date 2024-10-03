#pragma once

#include "Common_PhysicsEngine.h"

namespace ChaosEngine {
    namespace PhysicsEngine {
        inline void get_linear_function(POINT p1, POINT p2, LINE& out_linear_fn) {
            out_linear_fn.k = (p2.y - p1.y) / (p2.x - p1.x);
            out_linear_fn.b = p1.y - out_linear_fn.k * p1.x;
            out_linear_fn.pp1 = &p1;
            out_linear_fn.pp2 = &p2;
        }
        inline bool is_collided(LINE& line1, LINE& line2, POINT& out_collision_point) {
            auto& out_p = out_collision_point;
            out_p.x = (line2.b - line1.b) / (line1.k - line2.k);
            out_p.y = line1.k * out_p.x + line1.b;
            if (line1.pp1 && line1.pp2) {
                if (out_p.x > line1.pp1->x) {
                    
                }
            }
            return false;
        }
    }
}

#include "GeoBox.cpp"
#include "PhysicalSpace.cpp"