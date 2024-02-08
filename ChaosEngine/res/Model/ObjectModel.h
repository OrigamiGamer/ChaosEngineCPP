#pragma once
#include "_list.h"

namespace ChaosEngine {

    namespace Type {

        struct STD_VEC_FORCE_LIST {
            std::vector<Type::FORCE>
                gravity,    // 引力
                friction,   // 摩擦力
                normal,     // 支持力
                tension,    // 张力
                magnetism,  // 磁力
                applied;    // 作用力
        };

    };

    namespace Model {

        class ObjectModel : public CompModel {
        public:
            Type::SIZE size{ 0, 0 };
            Type::POS pos{ 0, 0 };

            bool use_physics = false;   // Do NOT use physics to this Object by default.
            bool fixed = false; // Do NOT fix this object by default.
            double mass = 0;    // kg
            double elastic_k = 1;   // elastic coefficient
            double force_x = 0;  // N
            double force_y = 0;  // N
            double velocity_x = 0;  // m/s
            double velocity_y = 0;  // m/s

            Type::STD_VEC_FORCE_LIST vec_force;

        public:
            ObjectModel() = default;

            void ApplyForce(const Type::FORCE& new_force) {
                vec_force.applied.push_back(new_force);
            };

            void ClearForce() {
                vec_force.applied.clear();
            };

            inline void ComposeForce(const Type::FORCE& new_force) {
                double ma = new_force.magnitude, di = new_force.direction;
                //force_x += ma * cos(-di);
                //force_y += ma * sin(-di);
                force_x += ma * cos(di);
                force_y += ma * sin(di);
            };

            inline bool IsCollided(const Type::POS& obj_pos, const Type::SIZE& obj_size) const {
                D2D1_RECT_F rs = { pos.x, pos.y, pos.x + size.width, pos.y + size.height };
                D2D1_RECT_F r = { obj_pos.x, obj_pos.y, obj_pos.x + obj_size.width, obj_pos.y + obj_size.height };
                bool _X = !(rs.left > r.right || rs.right < r.left);
                bool _Y = !(rs.top > r.bottom || rs.bottom < r.top);
                return _X && _Y;
            };
            inline bool IsCollided(Model::ObjectModel& obj) const {
                return IsCollided(obj.pos, obj.size);
            };
            inline bool IsCollided(Model::ObjectModel*& obj) const {
                return IsCollided(obj->pos, obj->size);
            };

        };

    }

}