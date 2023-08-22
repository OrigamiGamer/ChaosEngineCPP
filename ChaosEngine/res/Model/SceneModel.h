#pragma once
#include "ModelList.h"

namespace ChaosEngine {

    namespace Model {

        class SceneModel : public ObjectModel {
        private:
            std::vector<CompModel*> vec_pComp;


        public:
            SceneModel() {};

            int Init() { return -3; };
            int Update() {
                for (int i = 0; i < vec_pComp.size(); i++) {
                    vec_pComp[i]->Update();
                };

                return -3;
            };
            int Render() { return -3; };
            int Release() { return -3; };


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
