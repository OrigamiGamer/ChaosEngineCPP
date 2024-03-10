#pragma once
#include "_list.cpp"

namespace ChaosEngine {

    namespace Model {

        SceneModel::SceneModel() {
            vec_pComp;
            vec_pObject;
        }

        void SceneModel::Update() {
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
        void SceneModel::RegComp(ObjectModel& AnyObject) {
            AnyObject.Init();
            vec_pObject.push_back(&AnyObject);
        };
        void SceneModel::RegComp(ObjectModel*& AnyObject) {
            (*AnyObject).Init();
            vec_pObject.push_back(AnyObject);
        };

    }

}
