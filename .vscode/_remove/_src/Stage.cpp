#pragma once
#include "Class.h"

namespace ChaosEngine {

    namespace Stage {

        std::vector<Model::SceneModel*> vec_pSceneRegistered;
        Model::SceneModel* pCurScene = nullptr; // Current Scene
        Model::SceneModel* pPreScene = nullptr; // Preparing Scene


        // State Update
        void StageUpdate() {

            // Initialize or release resources while switching scene.
            if (pCurScene == pPreScene) {
                if (pCurScene != nullptr) {
                    // Update Logic
                    pCurScene->SceneModel::Update();    // Update the logic in model at first,
                    pCurScene->Update();    // then update the logic of scene.

                    // Update PhysicX
                    PhysicX::PhysicXUpdate(pCurScene->vec_pObject, EngineX::deltaTime);
                }
            }
            else if (pCurScene->OnSceneExiting()) { // User confirms closing the current scene.
                // Update in the same way.
                if (pPreScene != nullptr) {
                    pPreScene->Update();
                    pPreScene->SceneModel::Update();
                }
                // Release resources in current scene, and switch to the new scene, preparing scene.
                pCurScene->SceneModel::Release();
                pCurScene->Release();
                pCurScene = pPreScene;
            }

        };

        // Stage Render
        void StageRender() {
            if (pCurScene != nullptr) {
                pCurScene->SceneModel::Render();  // Render in the same way to update.
                pCurScene->Render();
            }

        };

        // Register a scene object to stage
        void RegScene(Model::SceneModel& AnyScene) {
            if (&AnyScene != nullptr) {
                vec_pSceneRegistered.push_back(&AnyScene);  // Register the new scene
                AnyScene.Init();    // Initialize the new scene

                if (!pCurScene) {
                    pCurScene = &AnyScene;
                    pPreScene = &AnyScene;
                }
            }
        };

        // Switch the current scene to target scene after an user's preparing process.
        void SwitchScene(Model::SceneModel& TargetScene) {
            pPreScene = &TargetScene;
        };

    }

}
