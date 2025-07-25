#pragma once

#include "AudioX/AudioX.h"

namespace Chaos::AudioX {
    Channel::Channel(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("Channel");
    }

    Channel::~Channel()
    {

    }
}