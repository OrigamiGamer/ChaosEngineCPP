#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace EngineX {
        


    };

    class Engine {
    public:
        Engine() {};

        BOOL Start(WindowInitialProperty WndProp, EngineStartupProperty EngineProp) {
            WindowX::InitWindow(WndProp);

            Property::Engine::ProcList = EngineProp.ProcList;
            if (Property::Engine::ProcList.GameInit > NULL) LRESULT lr = Property::Engine::ProcList.GameInit();

            WindowX::StartMessageLoop();


            return true;
        };

        BOOL Release() {

            return true;
        };

    };

}
