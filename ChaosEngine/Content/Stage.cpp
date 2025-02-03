#pragma once

#include "Common.h"

namespace Chaos::Content {
    Stage::Stage(Device::Engine* new_engine)
    {
        this->engine = new_engine;
    }

    Stage::~Stage()
    {

    }
}