#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace Stage {
        extern std::vector<Model::SceneModel*> vec_pSceneRegistered;
        extern Model::SceneModel* pCurScene;
        extern Model::SceneModel* pPreScene;

        void StageUpdate();
        void StageRender();
        void SwitchScene(Model::SceneModel& TargetScene);
        void RegScene(Model::SceneModel& AnyScene);

    }

}
