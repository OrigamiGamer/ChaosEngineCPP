#pragma once

#include "chaos/device/device.h"


namespace chaos::device {



    struct EngineStartupProperty {
        unsigned int fps = 60;
        Callback_GameInit onGameInit = nullptr;
        Callback_GameExit onGameExit = nullptr;
    };



}