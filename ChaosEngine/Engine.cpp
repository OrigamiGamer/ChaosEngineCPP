#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* Engine */
    namespace Engine {

        BOOL Start(Type::WindowInitialProperty& WndProp, Type::EngineStartupProperty& EngineProp) {
            if (WindowX::InitWindow(&WndProp) == NULL) return FALSE;
            Property::Engine::StartupProp = &EngineProp;
            
            WindowX::StartMessageLoop();

            return TRUE;
        };

        BOOL Release() {
            WindowX::ReleaseDirectX();

            return TRUE;
        };

    }

}
