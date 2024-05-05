#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace EngineX {
        extern Type::EngineStartupProperty* pStartupProp;
        extern long double lastTime;
        extern long double curTime;
        extern long double deltaTime;

        HRESULT Initialize(Type::EngineStartupProperty& EngineProp, Type::WindowInitialProperty& WndProp);
        HRESULT EngineInit();
        HRESULT EngineUpdate();
        HRESULT EngineRender();
        HRESULT EngineExit();
    }

}