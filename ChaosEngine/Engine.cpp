#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* Engine */
    namespace Engine {

        BOOL Start(Type::WindowInitialProperty& WndProp, Type::EngineStartupProperty& EngineProp) {
            Property::Engine::StartupProp = &EngineProp;

            if (WindowX::InitWindow(&WndProp) == NULL) return FALSE;
            WindowX::StartMessageLoop();

            return TRUE;
        };

        BOOL Release() {
            WindowX::ReleaseDirectX();

            return TRUE;
        };

    }

}
