#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* EngineX for processing engine logic */
    namespace EngineX {

        namespace SafeAccessScene {

            LRESULT InitScene(Model::SceneModel* new_scene);
            LRESULT UpdateScene(Model::SceneModel* new_scene);
            LRESULT RenderScene(Model::SceneModel* new_scene);

        };

        LRESULT EngineInit();
        LRESULT EngineUpdate();
        LRESULT EngineRender();
        LRESULT EngineExit();

    }

}
