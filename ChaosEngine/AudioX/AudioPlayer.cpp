#pragma once

#include "AudioX/AudioX.h"

namespace Chaos::AudioX {



    AudioPlayer::AudioPlayer(InternalDevice::Engine* new_engine)
    {
        this->engine = new_engine;
        this->INIT("AudioPlayer");
    }



    AudioPlayer::~AudioPlayer()
    {

    }


    
}