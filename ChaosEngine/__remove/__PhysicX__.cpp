#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace PhysicX {
        const double GRAVITY = 6.67 * pow(10, -11);
        
        Type::POS GetCenterPos(Type::POS& obj_pos, Type::SIZE& obj_size) {
            return { (obj_pos.x + obj_size.width) / 2, (obj_pos.y + obj_size.height) / 2 };
        }; 
        Type::POS GetCenterPos(Model::ObjectModel*& obj) {
            return GetCenterPos(obj->pos, obj->size);
        };

        double GetDistance(Model::ObjectModel*& obj_1, Model::ObjectModel*& obj_2) {
            if (obj_1 && obj_2) {
                Type::POS pos_1 = GetCenterPos(obj_1);
                Type::POS pos_2 = GetCenterPos(obj_2);
                return sqrt(pow(pos_2.x - pos_1.x, 2) + pow(pos_2.y - pos_1.y, 2));
            };
            return NULL;
        };

        double GetDirection(Model::ObjectModel*& obj_self, Model::ObjectModel*& obj_reference) {
            if (obj_self && obj_reference) {
                Type::POS& pos_s = GetCenterPos(obj_self);
                Type::POS& pos_r = GetCenterPos(obj_reference);
                return static_cast<double>(std::atanf((pos_r.y - pos_s.y) / (pos_r.x - pos_s.x)));
            };
            return NULL;
        };

        Type::FORCE ComputeGravity(Model::ObjectModel*& obj, Model::ObjectModel*& obj_apply) {
            if (obj && obj_apply) {
                return Type::FORCE(
                    GRAVITY * (obj->mass / pow(GetDistance(obj, obj_apply), 2)),
                    GetDirection(obj, obj_apply)
                );
            };
            return {};
        };

        void PhysicXUpdate(std::vector<Model::ObjectModel*>& objs, long double& deltaTime) {
            // foreach all objects
            for (int i = 0; i < objs.size(); i++) {
                Model::ObjectModel*& obj = objs[i];
                if (obj->use_physics) {
                    Type::STD_VEC_FORCE_LIST& vec_force = obj->vec_force;

                    // clear forces
                    vec_force.gravity.clear();

                    // compose forces, foreach objects except itself
                    for (int j = 0; j < objs.size(); j++) {
                        Model::ObjectModel*& _obj = objs[j];
                        if (objs[j] != obj) {
                            Type::FORCE& gravity = ComputeGravity(obj, _obj);

                            vec_force.gravity.push_back(gravity);

                            // [Colliding Logic] -> vec_force.normal or friction
                            if (obj->IsCollided(_obj)) {
                                // collided, compute normal force
                                
                                // DEBUG - Compute Elasticity //
                                //Type::SIZE& size = obj->size;
                                //Type::SIZE& _size = _obj->size;
                                
                                //double dist = GetDistance(obj, _obj);
                                //double di = GetDirection(obj, _obj);
                                //Type::FORCE elasticity = Type::FORCE(dist,);

                                // centerPos, F=k*x
                                // box:{rect, circle}
                            };

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
                    obj->pos.x += static_cast<float>(obj->velocity_x * deltaTime);
                    obj->pos.y += static_cast<float>(obj->velocity_y * deltaTime);

                };
            };
        };
    }

}
