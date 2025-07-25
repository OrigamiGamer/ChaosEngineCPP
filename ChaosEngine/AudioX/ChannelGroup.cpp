#pragma once

#include "AudioX/AudioX.h"

namespace Chaos::AudioX {
    ChannelGroup::ChannelGroup(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("ChannelGroup"); 

    }

    ChannelGroup::~ChannelGroup()
    {

    }
}