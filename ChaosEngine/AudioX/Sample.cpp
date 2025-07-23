#pragma once

#include "AudioX/AudioX.h"

namespace Chaos::Audio {
    Sample::Sample(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("Sample");

    }

    Sample::~Sample()
    {

    }
}
