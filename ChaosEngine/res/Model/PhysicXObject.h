#pragma once
#include "ModelList.h"

namespace ChaosEngine {

    namespace Model {

        class PhysicXObject : public ObjectModel {
        private:
            DOUBLE self_mass = 0;

        public:
            ObjectModel() {};

            void Init() {};
            void Update() {};
            void Render() {};
            void Release() {};

            void SetMass(DOUBLE mass) {
                self_mass = mass;
            };
            DOUBLE GetMass() {
                return self_mass;
            };

        };

    }

}