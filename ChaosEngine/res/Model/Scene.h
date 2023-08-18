#pragma once
#include "ModelList.h"

namespace ChaosEngine {

    namespace Model {

        class Scene : public ObjectModel {
        public:
            Scene() {};

            int Init() {
                return -2;
            };
            int Update() {
                return -2;
            };
            int Render() {
                return -2;
            };
            int Release() {
                return -2;
            };
            virtual int OnSceneEntered() {
                return -2;
            };
            virtual bool OnSceneExiting() {
                return true;    // true returned means confirmed to exit.
            };

        };

    }

}
