#pragma once

#include "AudioX/AudioX.h"

namespace Chaos::Audio {
    Sound::Sound(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("Sound");

    }

    Sound::~Sound()
    {

    }
}