#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace PhysicX {

        void PhysicXUpdate(std::vector<Model::ObjectModel*>& objs, FLOAT& deltaTime) {
            for (int i = 0; i < objs.size(); i++) {
                Model::ObjectModel* obj = objs[i];
                if (obj->use_physics) {

                    // compose forces
                    for (int j = 0;j < obj->vec_force.size();j++) {
                        Type::FORCE* F = &(obj->vec_force[j]);
                        float& ma = F->magnitude;
                        float& di = F->direction;
                        
                        // "+x" axis is the 0 rad
                        obj->force_x += ma * cos(-di);
                        obj->force_y += ma * sin(-di);
                    };
                    
                    // a = f / m
                    float a_x = obj->force_x / obj->mass;
                    float a_y = obj->force_y / obj->mass;
                    // v = a * t
                    obj->velocity_x += a_x * deltaTime;
                    obj->velocity_y += a_y * deltaTime;
                    // s = v * t
                    obj->pos.x += obj->velocity_x * deltaTime;
                    obj->pos.y += obj->velocity_y * deltaTime;

                };
            };
        };
    }

}
