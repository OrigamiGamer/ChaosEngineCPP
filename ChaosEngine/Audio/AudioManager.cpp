#pragma once

#include "Common.h"

namespace Chaos::Audio {
    AudioManager::AudioManager(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);
        this->INIT("AudioManager");

    }
    AudioManager::~AudioManager()
    {

    }
}