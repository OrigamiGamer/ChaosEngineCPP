#pragma once
#include "_list.h"

namespace ChaosEngine {

    namespace Model {

        class SceneModel : public ObjectModel {
        public:

            std::vector<CompModel*> vec_pComp;
            std::vector<ObjectModel*> vec_pObject;

            SceneModel();

            void Update();
            void Render();
            virtual int OnSceneEntered();
            virtual bool OnSceneExiting();

            // Register a component or an object to this scene, initialize it before success immediately.
            void RegComp(CompModel& AnyComp);
            void RegComp(ObjectModel& AnyObject);
            void RegComp(ObjectModel*& AnyObject);
        };

    }

}
