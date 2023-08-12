#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace Model {

        class Object {
        private:
            Type::SIZE self_size;
            Type::POS self_pos;
        public:
            Object() {};

            virtual void Init() {};
            virtual void Update() {};
            virtual void Render() {};
            virtual void Release() {};

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

        class Scene : public Object {
        public:
            Scene() {};

            void Init() {

            };
            void Update() {

            };
            void Render() {

            };
            void Release() {

            };

        };

    }

    void _debug() {
        Model::Scene scene = Model::Scene();
        scene.SetSize(111, empty);

    };

}