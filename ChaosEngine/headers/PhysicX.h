#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace PhysicX {
        extern void PhysicXUpdate(std::vector<Model::ObjectModel*>& objs, FLOAT& deltaTime);
    }

}
