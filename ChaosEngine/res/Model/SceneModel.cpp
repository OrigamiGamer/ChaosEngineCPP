#pragma once
#include "_list.cpp"

namespace ChaosEngine {

    namespace Model {

        SceneModel::SceneModel() {
            vec_pComp;
            vec_pObject;
            pCurCamera = nullptr;
            pPreCamera = nullptr;
        }

        void SceneModel::Init() { };

        void SceneModel::Update() {

            // Switch the current camera to preparing camera.
            if (pCurCamera == pPreCamera) {
                pCurCamera->Update();
            }
            else if (SceneModel::OnCameraEntered()) {
                if (pPreCamera != nullptr) pPreCamera->Update();
                pCurCamera = pPreCamera;
            }

            // Update the Object or Component registered to this scene.
            for (CompModel* pComp : vec_pComp) {
                pComp->Update();
            }
            for (ObjectModel* pObject : vec_pObject) {
                pObject->Update();
            }
        };

        void SceneModel::Render() {
            for (CompModel* pComp : vec_pComp) {
                pComp->Render();
            }
            for (ObjectModel* pObject : vec_pObject) {
                pObject->Render();
            }
        };

        // Return value is custom.
        int SceneModel::OnSceneEntered() {
            return -1;
        };
        int SceneModel::OnCameraEntered() {
            return -1;
        };
        // Value 'true' returned means confirmed to exit.
        bool SceneModel::OnSceneExiting() {
            return true;
        };
        bool SceneModel::OnCameraExiting() {
            return true;
        };

        // Register a component or an object to this scene, initialize it before success immediately.
        void SceneModel::RegComp(CompModel& AnyComp) {
            AnyComp.Init();
            vec_pComp.push_back(&AnyComp);
        };
        void SceneModel::RegComp(CompModel*& AnyComp) {
            AnyComp->Init();
            vec_pComp.push_back(AnyComp);
        };
        void SceneModel::RegComp(ObjectModel& AnyObject) {
            AnyObject.pCamera = pCurCamera;
            AnyObject.Init();
            vec_pObject.push_back(&AnyObject);
        };
        void SceneModel::RegComp(ObjectModel*& AnyObject) {
            AnyObject->pCamera = pCurCamera;
            (*AnyObject).Init();
            vec_pObject.push_back(AnyObject);
        };
        
        // Switch the current camera to preparing camera after an user's preparing process.
        void SceneModel::SwitchCamera(Type::Camera& TargetCamera) {
            pPreCamera = &TargetCamera;
        };

    }

}
