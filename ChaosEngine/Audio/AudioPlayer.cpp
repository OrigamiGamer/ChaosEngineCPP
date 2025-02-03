#pragma once

#include "Common.h"

namespace Chaos::Audio {
    AudioPlayer::AudioPlayer(Device::Engine* new_engine)
    {
        this->engine = new_engine;

    }

    AudioPlayer::~AudioPlayer()
    {

    }
}