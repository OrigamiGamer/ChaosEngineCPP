#pragma once

#include "Common.h"

namespace Chaos::Audio {
    AudioManager::AudioManager(Device::Engine* new_engine)
    {
        this->engine = new_engine;

    }
    AudioManager::~AudioManager()
    {

    }
}