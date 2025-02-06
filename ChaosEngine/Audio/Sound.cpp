#pragma once

#include "Common.h"

namespace Chaos::Audio {
    Sound::Sound(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);
        this->INIT("Sound");

    }

    Sound::~Sound()
    {

    }
}