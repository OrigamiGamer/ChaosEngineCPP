#pragma once
#include "ModelList.h"

namespace ChaosEngine {

    namespace Model {

        class Object {
        private:
            Type::SIZE self_size;
            Type::POS self_pos;

        public:
            Object() {};

            virtual int Init() { return -1; };
            virtual int Update() { return -1; };
            virtual int Render() { return -1; };
            virtual int Release() { return -1; };

        public:
            void SetSize(Type::SIZE new_size) {
                SET_OPT(self_size.width, new_size.width);
                SET_OPT(self_size.height, new_size.height);
            };
            void SetSize(float width, float height) {
                SET_OPT(self_size.width, width);
                SET_OPT(self_size.height, height);
            };

            void SetPos(Type::POS new_pos) {
                SET_OPT(self_pos.x, new_pos.y);
                SET_OPT(self_pos.y, new_pos.y);
            };
            void SetPos(float x, float y) {
                SET_OPT(self_pos.x, x);
                SET_OPT(self_pos.y, y);
            };

        };



    }

}