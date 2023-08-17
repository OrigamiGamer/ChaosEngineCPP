#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* Engine */
    namespace Engine {

        BOOL Start(Type::WindowInitialProperty* WndProp, Type::EngineStartupProperty* EngineProp) {
            WindowX::InitWindow(WndProp);
            Property::Engine::StartupProp = EngineProp;

            WindowX::StartMessageLoop();

            return true;
        };

        BOOL Release() {
            WindowX::ReleaseDirectX();

            return true;
        };

        namespace Stage {

            void SwitchScene(Model::Scene* pTargetScene) {
                if (pTargetScene != NULL)
                    EngineX::pNextScene = pTargetScene;
            };

            void RegScene(Model::Scene* pAnyScene) {
                if (pAnyScene != NULL) {
                    if (EngineX::pCurrentScene == NULL) {
                        EngineX::pCurrentScene = pAnyScene;
                        EngineX::pNextScene = EngineX::pCurrentScene;   // Switch to initial scene directly
                    }

                    EngineX::pSceneArray.push_back(pAnyScene);  // Register the new scene
                }

            };

        }

    }
}