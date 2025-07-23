#pragma once

#include "AudioX/AudioX.h"

namespace Chaos::Audio {
    ChannelGroup::ChannelGroup(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("ChannelGroup"); 

    }

    ChannelGroup::~ChannelGroup()
    {

    }
}