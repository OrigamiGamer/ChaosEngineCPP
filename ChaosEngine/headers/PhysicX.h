#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace PhysicX {
        extern Type::POS GetCenterPos(Type::POS& obj_pos, Type::SIZE& obj_size);
        extern Type::POS GetCenterPos(Model::ObjectModel*& obj);
        extern double GetDistance(Model::ObjectModel*& obj_1, Model::ObjectModel*& obj_2);
        extern double GetDirection(Model::ObjectModel*& obj_self, Model::ObjectModel*& obj_reference);
        extern Type::FORCE ComputeGravity(Model::ObjectModel*& obj, Model::ObjectModel*& obj_apply);

        extern void PhysicXUpdate(std::vector<Model::ObjectModel*>& objs, long double deltaTime);
    }

}
