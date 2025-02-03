#pragma once

#include "Common.h"

namespace Chaos::Content {
    Actor::Actor(Device::Engine* new_engine)
    {
        this->engine = new_engine;

    }

    Actor::~Actor()
    {
        
    }
}