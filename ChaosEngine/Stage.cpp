#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace Stage {

        std::vector<Model::SceneModel*> vec_pSceneRegistered;
        Model::SceneModel* pCurScene = nullptr; // Current Scene
        Model::SceneModel* pPreScene = nullptr; // Preparing Scene

        CompList::Camera* pCurCamera = nullptr; // Current Camera

        // State Update
        void StageUpdate() {
            if (pCurCamera != nullptr)
                WindowX::Prop::MouseOffsetPos = WindowX::Prop::MousePos + pCurCamera->viewPos; // Update the mouse offset position.

            if (pCurScene == pPreScene) {
                if (pCurScene != nullptr) {
                    // Update Logic
                    pCurScene->SceneModel::Update();    // Update the logic in model at first,
                    pCurScene->Update();    // then update the logic of scene.

                    // Update PhysicX
                    PhysicX::PhysicXUpdate(pCurScene->vec_pObject, EngineX::deltaTime);

                };
            }
            else if (pCurScene->OnSceneExiting()) { // User confirms closing the current scene.
                pPreScene->SceneModel::Update(); // Update in the same way.
                if (pPreScene != nullptr) pPreScene->Update();
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

        // Switch to a target scene as the current scene
        void SwitchScene(Model::SceneModel& TargetScene) {
            if (&TargetScene != nullptr) pPreScene = &TargetScene;
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

    }

}
