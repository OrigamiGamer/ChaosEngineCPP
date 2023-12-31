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
            
        public:
            ObjectModel() {};

            void AddForce(Type::FORCE new_force) {
                float& ma = new_force.magnitude;
                float& di = new_force.direction;

                // "+x" axis is the 0 rad
                force_x += ma * cos(di);
                force_y += ma * sin(di);

            };

        };



    }

}