#pragma once

#include "Common.h"

namespace Chaos::Audio {
    ChannelGroup::ChannelGroup(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);

    }

    ChannelGroup::~ChannelGroup()
    {

    }
}