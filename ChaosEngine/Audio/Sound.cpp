#pragma once

#include "Common.h"

namespace Chaos::Audio {
    Sound::Sound(Device::Engine* new_engine)
    {
        this->engine = new_engine;

    }

    Sound::~Sound()
    {

    }
}