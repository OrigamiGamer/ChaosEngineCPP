#pragma once

#include "AudioX/AudioX.h"

namespace Chaos::Audio {
    AudioManager::AudioManager(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("AudioManager");

    }
    AudioManager::~AudioManager()
    {

    }
}