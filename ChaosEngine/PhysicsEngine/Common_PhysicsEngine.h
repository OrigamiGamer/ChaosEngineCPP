#pragma once

#include "Common.h"

namespace ChaosEngine {
    namespace PhysicsEngine {
        typedef basic_type::vec2<double> POINT;

        struct LINE {
            POINT* pp1 = nullptr;
            POINT* pp2 = nullptr;
            double k;
            double b;
        };

        inline void get_linear_function(POINT p1, POINT p2, LINE& out_linear_fn);
        inline bool is_collided(LINE& linear_fn1, LINE& linear_fn2, POINT& out_collision_point);

        class GeoBox;
        class PhysicalSpace;
    }
}

#include "GeoBox.h"
#include "PhysicalSpace.h"