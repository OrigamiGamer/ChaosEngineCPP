#pragma once
#include "ModelList.h"

namespace ChaosEngine {

    namespace Model {

        class Scene : public Object {
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

            virtual bool OnClose() {
                return true;    // true returned means confirmed to close.
            };

        };

    }

}
