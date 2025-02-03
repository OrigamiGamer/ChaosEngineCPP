#pragma once

#include "Common.h"

namespace Chaos::Audio {
    AudioPlayer::AudioPlayer(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);

    }

    AudioPlayer::~AudioPlayer()
    {

    }
}