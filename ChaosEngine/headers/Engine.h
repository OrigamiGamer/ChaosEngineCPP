#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* Engine */
    namespace Engine {

        BOOL Start(Type::WindowInitialProperty& WndProp, Type::EngineStartupProperty& EngineProp);
        BOOL Release();

    }

}