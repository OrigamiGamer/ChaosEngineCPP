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

            pCurCamera->Update();

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

        int SceneModel::OnSceneEntered() {
            return -1;
        };
        bool SceneModel::OnSceneExiting() {
            return true;    // true returned means confirmed to exit.
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

        void SceneModel::SwitchCamera(Type::Camera& TargetCamera) {
            pPreCamera = &TargetCamera;
            pCurCamera = pPreCamera;  // TODO
            
            for (size_t i = 0; i < vec_pObject.size(); i++) {
                vec_pObject[i]->pCamera = pCurCamera;
            }

        };

    }

}
