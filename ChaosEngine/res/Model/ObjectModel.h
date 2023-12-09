#pragma once
#include "ModelList.h"

namespace ChaosEngine {

    namespace Model {

        class ObjectModel : public CompModel {
        private:
            Type::SIZE self_size{};
            Type::POS self_pos{};

        public:
            BOOL use_physics = FALSE;   // Do NOT use physics to this Object by default.
            FLOAT mass = 0;    // kg
            FLOAT force_x = 0;  // N
            FLOAT force_y = 0;  // N
            FLOAT velocity_x = 0;  // m/s
            FLOAT velocity_y = 0;  // m/s
            
        public:
            ObjectModel() {};

            void Init() {};
            void Update() {};
            void Render() {};
            void Release() {};


            void SetSize(Type::SIZE new_size) {
                SET_OPT(self_size.width, new_size.width);
                SET_OPT(self_size.height, new_size.height);
            };
            void SetSize(float width, float height) {
                SET_OPT(self_size.width, width);
                SET_OPT(self_size.height, height);
            };
            Type::SIZE GetSize() const {
                return self_size;
            };

            void SetPos(Type::POS new_pos) {
                SET_OPT(self_pos.x, new_pos.y);
                SET_OPT(self_pos.y, new_pos.y);
            };
            void SetPos(float x, float y) {
                SET_OPT(self_pos.x, x);
                SET_OPT(self_pos.y, y);
            };
            Type::POS GetPos() const {
                return self_pos;
            };

            void AddForce(Type::FORCE new_force) {
                float& ma = new_force.magnitude;
                float& di = new_force.direction;

                if (0 <= di && di <= 90) {
                    force_x += ma * cos(di);
                    force_y += ma * sin(di);
                }
                else if (90 < di && di <= 180) {
                    force_x -= ma * sin(di);
                    force_y += ma * cos(di);
                }
                else if (180 < di && di <= 270) {
                    force_x -= ma * cos(di);
                    force_y -= ma * sin(di);
                }
                else if (270 < di && di <= 360) {
                    force_x += ma * sin(di);
                    force_y -= ma * cos(di);
                }

            };

        };



    }

}