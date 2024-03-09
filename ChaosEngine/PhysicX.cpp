#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace PhysicX {
        // 6.67e-11
        const double GRAVITY = 6.67;    // notice transition between realistic(meter) and virtual(piexl) unit
        
        // Get the center position of object
        inline Type::POS GetCenterPos(Type::POS& obj_pos, Type::SIZE& obj_size) {
            return { (obj_pos.x + obj_size.width) / 2, (obj_pos.y + obj_size.height) / 2 };
        }
        inline static Type::POS GetCenterPos(Model::ObjectModel*& obj) {
            return GetCenterPos(obj->pos, obj->size);
        }

        // Get the distance between objects
        inline static double GetDistance(Model::ObjectModel*& obj_1, Model::ObjectModel*& obj_2) {
             Type::POS pos_1 = GetCenterPos(obj_1);
             Type::POS pos_2 = GetCenterPos(obj_2);
            return sqrt(pow(pos_2.x - pos_1.x, 2) + pow(pos_2.y - pos_1.y, 2));
        }

        // Get the direction from object itself to reference object
        inline static double GetDirection(Model::ObjectModel*& obj_self, Model::ObjectModel*& obj_reference) {
             Type::POS pos_s = GetCenterPos(obj_self);
             Type::POS pos_r = GetCenterPos(obj_reference);
             return static_cast<double>(std::atan2f(pos_r.y - pos_s.y, pos_r.x - pos_s.x));
        }

        // Compute gravity
        inline static Type::FORCE ComputeGravity(Model::ObjectModel*& obj, Model::ObjectModel*& obj_apply) {
             double dist = GetDistance(obj, obj_apply);
             double di = GetDirection(obj, obj_apply);
             return { GRAVITY * ((obj->mass * obj_apply->mass) / (dist * dist)), di, Type::FORCE_TYPE_GRAVITY };
        }

        void PhysicXUpdate(std::vector<Model::ObjectModel*>& objs, long double deltaTime) {

            // foreach all objects
            for (int i = 0; i < objs.size(); i++) {
                Model::ObjectModel*& obj = objs[i];
                if (obj->use_physics) {
                    Type::STD_VEC_FORCE_LIST& vec_force = obj->vec_force;

                    // clear forces
                    vec_force.gravity.clear();

                    obj->force_x = 0;
                    obj->force_y = 0;

                    // compose forces, foreach objects except itself(obj)
                    for (int j = 0; j < objs.size(); j++) {
                        Model::ObjectModel*& _obj = objs[j];
                        // except itself(obj)
                        if (obj != _obj) {
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


                    // finally compose applied forces
                    for (int m = 0; m < objs[i]->vec_force.applied.size(); m++) {
                        obj->ComposeForce(vec_force.applied[m]);
                    };


                    // compose forces
                    //for (int j = 0;j < obj->vec_force.gravity.size();j++) {
                    //    Type::FORCE* F = &(obj->vec_force.applied[j]);// 2:2, 3:6, 4:12, 5,20
                    //    // n:(n-1)*n
                    //};


                    // a = F / m
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
