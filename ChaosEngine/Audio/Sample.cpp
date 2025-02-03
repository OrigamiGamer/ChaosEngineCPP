#pragma once

#include "Common.h"

namespace Chaos::Audio {
    Sample::Sample(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);

    }

    Sample::~Sample()
    {

    }
}
