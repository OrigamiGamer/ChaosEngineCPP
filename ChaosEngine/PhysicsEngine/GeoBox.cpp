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
            // foreach vertex in vec_vertex to get linear function between it and next vertex
            for (size_t i = 0; i < this->vec_vertex.size(); i++) {
                size_t j = (i == this->vec_vertex.size() - 1) ? 0 : i + 1;  // connect to first vertex if last vertex
                auto& this_vertex = this->vec_vertex[i];
                auto& next_vertex = this->vec_vertex[j];
                get_linear_function(this_vertex, next_vertex, this->vec_linear_fn[i]);
            }
        }
        bool GeoBox::IsCollided(GeoBox& other_box) {
            if (this->z_order == other_box.z_order) {
                for (size_t i = 0; i < this->vec_linear_fn.size(); i++) {
                    for (size_t j = 0; j < other_box.vec_linear_fn.size(); j++) {
                        POINT _p;
                        get_collision_point(this->vec_linear_fn[i], other_box.vec_linear_fn[j], _p);
                        if (_p.x >= 0 && _p.x <= 1 && _p.y >= 0 && _p.y <= 1);
                    }
                }
            }
            return false;
        }
    }
}