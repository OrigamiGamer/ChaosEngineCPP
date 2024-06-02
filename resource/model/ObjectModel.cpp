#pragma once
#include "ResList.cpp"

namespace ChaosEngine {

    namespace Model {

        ObjectModel::ObjectModel() {
            pCamera = nullptr;

            size = { 0, 0 };
            anchorPos = { 0, 0 }; // anchor position related to the size.
            scale = { 1, 1, 1 };
            pos = { 0, 0 };
            rotation = 0;

            use_physics = false;   // Do NOT use physics to this Object by default.
            fixed = false; // Do NOT fix this object by default.
            mass = 0;    // kg
            elastic_k = 1;   // elastic coefficient
            force_x = 0;  // N
            force_y = 0;  // N
            velocity_x = 0;  // m/s
            velocity_y = 0;  // m/s

            vec_force;
        }

        void ObjectModel::SetAnchorPosInSite() {

        }

        inline Type::POS ObjectModel::GetAbsAnchorPos() {
            return pos + anchorPos; // so complex relative position!!!! wtf!
        }

        inline Type::POS ObjectModel::GetOriginPos() {
            return pos - anchorPos * scale;
        };

        inline Type::SIZE ObjectModel::GetOriginSize() {
            return size * scale;
        }

        inline Type::POS ObjectModel::GetRenderPos() {
            if (pCamera != nullptr) return GetOriginPos() - pCamera->viewPos;
            return {};
        }

        inline Type::SIZE ObjectModel::GetRenderSize() {
            if (pCamera != nullptr) return GetOriginSize() * pCamera->viewScale;
            return {};
        }

        void ObjectModel::ApplyForce(const Type::FORCE& new_force) {
            vec_force.applied.push_back(new_force);
        };

        void ObjectModel::ClearForce() {
            vec_force.applied.clear();
        };

        inline void ObjectModel::ComposeForce(const Type::FORCE& new_force) {
            double ma = new_force.magnitude, di = new_force.direction;
            //force_x += ma * cos(-di);
            //force_y += ma * sin(-di);
            force_x += ma * cos(di);
            force_y += ma * sin(di);
        };

        inline bool ObjectModel::IsCollided(const Type::POS& obj_pos, const Type::SIZE& obj_size) const {
            D2D1_RECT_F rs = { pos.x, pos.y, pos.x + size.width, pos.y + size.height };
            D2D1_RECT_F r = { obj_pos.x, obj_pos.y, obj_pos.x + obj_size.width, obj_pos.y + obj_size.height };
            bool _X = !(rs.left > r.right || rs.right < r.left);
            bool _Y = !(rs.top > r.bottom || rs.bottom < r.top);
            return _X && _Y;
        };
        inline bool ObjectModel::IsCollided(Model::ObjectModel& obj) const {
            return IsCollided(obj.pos, obj.size);
        };
        inline bool ObjectModel::IsCollided(Model::ObjectModel*& obj) const {
            return IsCollided(obj->pos, obj->size);
        };

    }

}