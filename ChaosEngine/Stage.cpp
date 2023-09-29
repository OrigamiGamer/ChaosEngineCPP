#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace Stage {

        void SwitchScene(Model::SceneModel& TargetScene) {
            if (&TargetScene)
                EngineX::pNextScene = &TargetScene;
        };

        void RegScene(Model::SceneModel& AnyScene) {
            if (&AnyScene) {
                EngineX::pSceneArray.push_back(&AnyScene);  // Register the new scene
                AnyScene.Init();    // Initialize the new scene

                if (EngineX::pCurScene == NULL) {
                    EngineX::pCurScene = &AnyScene;
                    EngineX::pNextScene = EngineX::pCurScene;   // As the initial scene to switch to it directly
                }

            }

        };

    }

}
