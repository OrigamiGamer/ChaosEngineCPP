#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace EngineX {
        extern Type::EngineStartupProperty* pStartupProp;
        extern long double lastTime;
        extern long double curTime;
        extern long double deltaTime;

        HRESULT Initialize(Type::EngineStartupProperty& EngineProp, Type::WindowInitialProperty& WndProp);
        LRESULT EngineInit();
        LRESULT EngineUpdate();
        LRESULT EngineRender();
        LRESULT EngineExit();
    }

}