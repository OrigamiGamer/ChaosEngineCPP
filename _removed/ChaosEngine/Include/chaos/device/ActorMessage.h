#pragma once

#include "chaos/device/device.h"


namespace chaos::device {



    struct ActorMessage {
        std::string actorType, actorName, content;
        bool isReceived = false;
    };



}