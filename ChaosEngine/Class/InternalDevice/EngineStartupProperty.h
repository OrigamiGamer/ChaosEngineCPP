#pragma once

#include "Class/InternalDevice/InternalDevice.h"



namespace Chaos::InternalDevice {



    struct EngineStartupProperty {
        unsigned int fps = 60;
        Callback_GameInit onGameInit = nullptr;
        Callback_GameExit onGameExit = nullptr;
    };



}