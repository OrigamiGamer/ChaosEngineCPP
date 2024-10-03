#pragma once

#include "Common_PhysicsEngine.h"

namespace ChaosEngine {
    namespace PhysicsEngine {
        class PhysicalSpace {
        public:
            POINT origin_pos;
            std::vector<GeoBox*> vec_collision_box;
        public:
            PhysicalSpace();
            inline void PushCollisionBox(GeoBox* new_box);
            void Update(unsigned long long delta_time);
        };
    }
}