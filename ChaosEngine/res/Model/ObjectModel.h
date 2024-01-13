#pragma once
#include "_list.h"

namespace ChaosEngine {

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

            // restore all forces, in order to show all forces(size and direction)
            std::vector<Type::FORCE> vec_force;

        public:
            ObjectModel() {};

            void AddForce(Type::FORCE new_force) {
                vec_force.push_back(new_force);
            };

            void ClearForce() {
                // force_x = 0;
                // force_y = 0;
                vec_force.clear();
            };
        };



    }

}