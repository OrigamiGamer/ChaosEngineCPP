#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace PhysicXEngine {

        void PhysicXUpdate(std::vector<Model::ObjectModel*> objs, FLOAT deltaTime) {
            for (int i = 0; i < objs.size(); i++) {
                float a_x = objs[i]->force_x / objs[i]->mass;
                float a_y = objs[i]->force_y / objs[i]->mass;
                objs[i]->velocity_x += a_x * deltaTime; // a * t
                // x = v * t
            };
        };

    }
}
