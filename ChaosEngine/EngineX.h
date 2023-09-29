#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* EngineX for processing engine logic */
    namespace EngineX {

        LRESULT EngineInit();
        LRESULT EngineUpdate();
        LRESULT EngineRender();
        LRESULT EngineExit();

    }

}
