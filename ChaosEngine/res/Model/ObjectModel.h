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

            BOOL use_physics = FALSE;   // Do NOT use physics to this Object by default.
            double mass = 0;    // kg
            double force_x = 0;  // N
            double force_y = 0;  // N
            double velocity_x = 0;  // m/s
            double velocity_y = 0;  // m/s

            Type::STD_VEC_FORCE_LIST vec_force;

        public:
            ObjectModel() {};
            
            void ApplyForce(Type::FORCE& new_force) {
                vec_force.applied.push_back(new_force);
            };

            void ClearForce() {
                vec_force.applied.clear();
            };

            void ComposeForce(Type::FORCE& new_force) {
                double ma = new_force.magnitude, di = new_force.direction;
                force_x += ma * cos(-di);
                force_y += ma * sin(-di);
            };

            BOOL IsCollided(Type::POS& obj_pos, Type::SIZE& obj_size) {
                D2D1_RECT_F& rs = { pos.x,pos.y,pos.x + size.width,pos.y + size.height };
                D2D1_RECT_F& r = { obj_pos.x,obj_pos.y,obj_pos.x + obj_size.width,obj_pos.y + obj_size.height };
                BOOL _X = !(rs.left > r.right || rs.right < r.left);
                BOOL _Y = !(rs.top > r.bottom || rs.bottom < r.top);
                return _X && _Y;
            };
            BOOL IsCollided(Model::ObjectModel& obj) {
                return IsCollided(obj.pos, obj.size);
            };
            BOOL IsCollided(Model::ObjectModel*& obj) {
                return IsCollided(obj->pos, obj->size);
            };

        };



    }

}