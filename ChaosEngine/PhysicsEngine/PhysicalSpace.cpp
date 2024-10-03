#pragma once

#include "PhysicalSpace.h"

namespace ChaosEngine {
    namespace PhysicsEngine {
        PhysicalSpace::PhysicalSpace() {
        }

        inline void PhysicalSpace::PushCollisionBox(GeoBox* new_box) {
            new_box->SetPhysicalSpace(this);
            this->vec_collision_box.push_back(new_box);
        }
        void PhysicalSpace::Update(unsigned long long delta_time) {
            for (auto& box : this->vec_collision_box) {
                box->Update();
            }
        }
    }
}