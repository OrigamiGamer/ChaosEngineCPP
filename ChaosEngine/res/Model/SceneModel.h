#pragma once
#include "ModelList.h"

namespace ChaosEngine {

    namespace Model {

        class SceneModel : public ObjectModel {
        public:
            std::vector<CompModel*> vec_pComp;
            std::vector<ObjectModel*> vec_pObject;

            SceneModel() {};

            void Init() {};
            void Update() {
                for (int i = 0; i < vec_pComp.size(); i++) {
                    vec_pComp[i]->Update();
                };
            };
            void Render() {
                for (int i = 0; i < vec_pComp.size(); i++) {
                    vec_pComp[i]->Render();
                };
            };
            void Release() {};


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
                vec_pObject.push_back(&AnyObject);
            };

        };

    }

}
