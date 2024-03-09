#pragma once
#include "_list.h"

namespace ChaosEngine {

    namespace Model {

        class SceneModel : public ObjectModel {
        public:
            
            std::vector<CompModel*> vec_pComp;
            std::vector<ObjectModel*> vec_pObject;

            SceneModel() {}

            void Update() {
                for (CompModel* pComp : vec_pComp) {
                    pComp->Update();
                }
                for (ObjectModel* pObject : vec_pObject) {
                    pObject->Update();
                }
            };
            void Render() {
                for (CompModel* pComp : vec_pComp) {
                    pComp->Render();
                }
                for (ObjectModel* pObject : vec_pObject) {
                    pObject->Render();
                }
            };

            virtual int OnSceneEntered() {
                return -1;
            };
            virtual bool OnSceneExiting() {
                return true;    // true returned means confirmed to exit.
            };

            // Register a component or an object to this scene, initialize it before success immediately.
            void RegComp(CompModel& AnyComp) {
                AnyComp.Init();
                vec_pComp.push_back(&AnyComp);
            };
            void RegComp(ObjectModel& AnyObject) {
                AnyObject.Init();
                vec_pObject.push_back(&AnyObject);
            };
            void RegComp(ObjectModel*& AnyObject) {
                (*AnyObject).Init();
                vec_pObject.push_back(AnyObject);
            };

        };

    }

}
