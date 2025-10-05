#pragma once

#include "Class/InternalDevice/InternalDevice.h"



namespace Chaos::InternalDevice {



    struct ActorMessage {
        std::string actorType, actorName, content;
        bool isReceived = false;
    };



}