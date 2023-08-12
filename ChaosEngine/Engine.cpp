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

            Property::Engine::GameInit = EngineProp.GameInit;
            Property::Engine::GameUpdate = EngineProp.GameUpdate;
            Property::Engine::GameRender = EngineProp.GameRender;
            Property::Engine::GameExit = EngineProp.GameExit;

            if (Property::Engine::GameInit > NULL) LRESULT lr = Property::Engine::GameInit();

            WindowX::StartMessageLoop();


            return true;
        };

        BOOL Release() {

            return true;
        };

    };

}
