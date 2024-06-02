#pragma once
#include "ResList.h"

namespace ChaosEngine {

    namespace Model {

        class SceneModel {
        public:

            std::vector<CompModel*> vec_pComp;
            std::vector<ObjectModel*> vec_pObject;
            Type::Camera* pCurCamera = nullptr; // Current Camera
            Type::Camera* pPreCamera = nullptr; // Preparing Camera
            bool is_release_on_switching = false;  // Do NOT release resources of scene on scene switching by default.

            SceneModel();

            virtual void Init();
            virtual void Update();
            virtual void Render();
            virtual void Release();
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
