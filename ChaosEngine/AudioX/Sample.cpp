#pragma once

#include "AudioX/AudioX.h"

namespace Chaos::AudioX {
    Sample::Sample(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("Sample");

    }

    Sample::~Sample()
    {

    }
}
