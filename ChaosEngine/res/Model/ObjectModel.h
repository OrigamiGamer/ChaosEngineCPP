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
            FLOAT mass = 0;    // kg
            FLOAT force_x = 0;  // N
            FLOAT force_y = 0;  // N
            FLOAT velocity_x = 0;  // m/s
            FLOAT velocity_y = 0;  // m/s

            Type::STD_VEC_FORCE_LIST vec_force;

        public:
            ObjectModel() {};
            
            void ApplyForce(Type::FORCE new_force) {
                vec_force.applied.push_back(new_force);
            };

            void ClearForce() {
                vec_force.applied.clear();
            };

            void ComposeForce(Type::FORCE new_force) {
                float ma = new_force.magnitude, di = new_force.direction;
                force_x += ma * cos(-di);
                force_y += ma * sin(-di);
            };

        };



    }

}