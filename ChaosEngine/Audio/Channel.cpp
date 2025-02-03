#pragma once

#include "Common.h"

namespace Chaos::Audio {
    Channel::Channel(Device::Engine* new_engine)
    {
        this->engine = new_engine;

    }

    Channel::~Channel()
    {

    }
}