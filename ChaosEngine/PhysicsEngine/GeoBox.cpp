#pragma once

#include "GeoBox.h"

namespace ChaosEngine {
    namespace PhysicsEngine {
        GeoBox::GeoBox() {
            this->space = nullptr;
        }
        GeoBox::GeoBox(PhysicalSpace* new_space) {
            SetPhysicalSpace(new_space);
        }

        inline bool GeoBox::SetPhysicalSpace(PhysicalSpace* new_space) {
            if (!new_space) return false;
            this->space = new_space;
            return true;
        }
        inline void GeoBox::AddNextVertex(POINT& new_vertex) {
            this->vec_vertex.push_back(new_vertex);
            this->vec_linear_fn.resize(vec_vertex.size());
        }
        void GeoBox::Update() {

        }
        bool GeoBox::IsCollided(GeoBox& other_box) {
            if (this->z_order == other_box.z_order) {
                
            }
            return false;
        }
    }
}