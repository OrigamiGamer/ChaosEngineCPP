#pragma once
#include "ModelList.h"

namespace ChaosEngine {

    namespace Model {

        class SceneModel : public ObjectModel {
        private:
            std::vector<CompModel*> vec_pComp;


        public:
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

            // Register a component obj to the scene obj, immediately init the component before success.
            void RegComp(CompModel& AnyComp) {
                vec_pComp.push_back(&AnyComp);

            };

        };

    }

}
