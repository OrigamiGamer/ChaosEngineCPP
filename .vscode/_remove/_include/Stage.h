#pragma once
#include "Class.h"

namespace ChaosEngine {

    namespace Stage {
        extern std::vector<Model::SceneModel*> vec_pSceneRegistered;
        extern Model::SceneModel* pCurScene;
        extern Model::SceneModel* pPreScene;

        void StageUpdate();
        void StageRender();
        void RegScene(Model::SceneModel& AnyScene);
        void SwitchScene(Model::SceneModel& TargetScene);

    }

}
