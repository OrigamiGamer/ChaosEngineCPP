#pragma once
#include "_list.h"

namespace ChaosEngine {

    namespace Model {

        class SceneModel : public ObjectModel {
        public:
            std::vector<CompModel*> vec_pComp;
            std::vector<ObjectModel*> vec_pObject;

            SceneModel() {};

            void Update() {
                for (int i = 0; i < vec_pComp.size(); i++) {
                    vec_pComp[i]->Update();
                };
                for (int i = 0; i < vec_pObject.size(); i++) {
                    vec_pObject[i]->Update();
                };
            };
            void Render() {
                for (int i = 0; i < vec_pComp.size(); i++) {
                    vec_pComp[i]->Render();
                };
                for (int i = 0; i < vec_pObject.size(); i++) {
                    vec_pObject[i]->Render();
                };
            };

            virtual int OnSceneEntered() {
                return -1;
            };
            virtual bool OnSceneExiting() {
                return true;    // true returned means confirmed to exit.
            };

            // Register a component to this scene, immediately init the component before success.
            void RegComp(CompModel& AnyComp) {
                AnyComp.Init();
                vec_pComp.push_back(&AnyComp);
            };

            void RegObject(ObjectModel& AnyObject) {
                AnyObject.Init();
                vec_pObject.push_back(&AnyObject);
            };

        };

    }

}
