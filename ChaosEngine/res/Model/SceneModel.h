#pragma once
#include "_list.h"

namespace ChaosEngine {

    namespace Model {

        class SceneModel {
        public:

            std::vector<CompModel*> vec_pComp;
            std::vector<ObjectModel*> vec_pObject;
            Type::Camera* pCurCamera = nullptr; // Current Camera
            Type::Camera* pPreCamera = nullptr; // Preparing Camera

            SceneModel();

            virtual void Init();
            virtual void Update();
            virtual void Render();
            virtual int OnSceneEntered();
            virtual int OnCameraEntered();
            virtual bool OnSceneExiting();
            virtual bool OnCameraExiting();

            void RegComp(CompModel& AnyComp);
            void RegComp(CompModel*& AnyComp);
            void RegComp(ObjectModel& AnyObject);
            void RegComp(ObjectModel*& AnyObject);
            void SwitchCamera(Type::Camera& TargetCamera);

        };

    }

}
