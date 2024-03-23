#pragma once
#include "_list.h"

namespace ChaosEngine {

    namespace Model {

        class SceneModel {
        public:

            std::vector<CompModel*> vec_pComp;
            std::vector<ObjectModel*> vec_pObject;
            Type::Camera* pCurCamera = nullptr; // Current Camera
            Type::Camera* pPreCamera = nullptr; // TODO: pPreCamera (like PreScene in Stage)

            SceneModel();

            virtual void Init();
            virtual void Update();
            virtual void Render();
            virtual int OnSceneEntered();
            virtual int OnCameraEntered();
            virtual bool OnSceneExiting();
            virtual bool OnCameraExiting();

            // Register a component or an object to this scene, initialize it before success immediately.
            void RegComp(CompModel& AnyComp);
            void RegComp(CompModel*& AnyComp);
            void RegComp(ObjectModel& AnyObject);
            void RegComp(ObjectModel*& AnyObject);
            void SwitchCamera(Type::Camera& TargetCamera);

        };

    }

}
