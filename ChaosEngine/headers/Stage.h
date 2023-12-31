#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace Stage {

        void StageUpdate();
        void StageRender();
        void SwitchScene(Model::SceneModel& TargetScene);
        void RegScene(Model::SceneModel& AnyScene);

    }

}
