#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace PhysicX {
        // 6.67e-11
        const double GRAVITY = 6.67e-11;    // notice transition between realistic(meter) and virtual(piexl) unit

        inline Type::POS GetCenterPos(Type::POS& obj_pos, Type::SIZE& obj_size);
        inline Type::POS GetCenterPos(Model::ObjectModel*& obj);
        inline double GetDistance(Model::ObjectModel*& obj_1, Model::ObjectModel*& obj_2);
        inline double GetDirection(Model::ObjectModel*& obj_self, Model::ObjectModel*& obj_reference);
        inline Type::FORCE ComputeGravity(Model::ObjectModel*& obj, Model::ObjectModel*& obj_apply);

        void PhysicXUpdate(std::vector<Model::ObjectModel*>& objs, long double deltaTime);
    }

}
