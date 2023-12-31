#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace Stage {

        std::vector<Model::SceneModel*> vec_pRegScene;
        Model::SceneModel* pCurScene = NULL;    // Current Scene
        Model::SceneModel* pPreScene = NULL;  // Preparing Scene

        /* Stage Update */
        void StageUpdate() {
            if (pCurScene == pPreScene) {
                if (pCurScene) {
                    // Update Logic
                    pCurScene->_update();  // Update the logic in model at first,
                    pCurScene->Update();    // then update the logic of scene.

                    // Update PhysicX
                    PhysicX::PhysicXUpdate(pCurScene->vec_pObject, Property::Engine::DeltaTime);

                };
            }
            else if (pCurScene->OnSceneExiting()) { // User confirms closing the current scene.
                pPreScene->_update(); // Update in the same way.
                if (pPreScene) pPreScene->Update();
                pCurScene = pPreScene;
            }
        };

        /* Stage Render */
        void StageRender() {
            if (pCurScene) {
                pCurScene->_render();  // Render in the same way to update.
                pCurScene->Render();
            }
        };

        /* Methods */

        void SwitchScene(Model::SceneModel& TargetScene) {
            if (&TargetScene) pPreScene = &TargetScene;
        };

        void RegScene(Model::SceneModel& AnyScene) {
            if (&AnyScene) {
                vec_pRegScene.push_back(&AnyScene);  // Register the new scene
                AnyScene.Init();    // Initialize the new scene

                if (!pCurScene) {
                    pCurScene = &AnyScene;
                    pPreScene = &AnyScene;
                }
            }
        };

    }

}
