#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace PhysicX {
        const double GRAVITY = 6.67 * pow(10, -11);
        
        double GetDistance(Model::ObjectModel* obj_1, Model::ObjectModel* obj_2) {
            if (obj_1 && obj_2) {
                return sqrtf((pow(obj_2->pos.x - obj_1->pos.x, 2) + pow(obj_2->pos.y - obj_1->pos.y, 2)));
            };
            return NULL;
        };

        double GetDirection(Model::ObjectModel* obj_self, Model::ObjectModel* obj_reference) {
            if (obj_self && obj_reference) {
                Model::ObjectModel*& obj_s = obj_self;
                Model::ObjectModel*& obj_r = obj_reference;
                return std::atanf(((obj_r->pos.y - obj_s->pos.y) / (obj_r->pos.x - obj_s->pos.x)));
            };
            return NULL;
        };

        Type::FORCE ComputeGravity(Model::ObjectModel* obj, Model::ObjectModel* obj_apply) {
            if (obj && obj_apply) {
                return Type::FORCE(
                    (GRAVITY * (obj->mass / pow(GetDistance(obj, obj_apply), 2))),
                    GetDistance(obj, obj_apply)
                );
            };
            return {};
        };

        void PhysicXUpdate(std::vector<Model::ObjectModel*>& objs, long double& deltaTime) {

            for (int i = 0; i < objs.size(); i++) {
                Model::ObjectModel*& obj = objs[i];

                if (obj->use_physics) {
                    Type::STD_VEC_FORCE_LIST& vec_force = obj->vec_force;

                    // clear forces
                    vec_force.gravity.clear();

                    // compose forces
                    for (int j = 0; j < objs.size(); j++) {
                        if (objs[j] != obj) {
                            Type::FORCE& gravity = ComputeGravity(obj, objs[j]);

                            vec_force.gravity.push_back(gravity);

                            // [Colliding Logic] -> vec_force.normal or friction


                            obj->ComposeForce(gravity);
                        };
                    };

                    // finally compose all kinds of forces
                    for (int m = 0; m < objs[i]->vec_force.gravity.size(); m++) {
                        obj->ComposeForce(vec_force.gravity[m]);
                    };


                    // compose forces
                    //for (int j = 0;j < obj->vec_force.gravity.size();j++) {
                    //    Type::FORCE* F = &(obj->vec_force.applied[j]);// 2:2, 3:6, 4:12, 5,20
                    //    // n:(n-1)*n
                    //};
                    
                    // a = f / m
                    double a_x = obj->force_x / obj->mass;
                    double a_y = obj->force_y / obj->mass;
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
