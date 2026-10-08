#pragma once

#include "Engine/Include/Core/Base.h"

namespace chaos::core {
    class String;
}

namespace chaos::audio {
    class AudioPlayer;
}

namespace chaos::audio {

    class AudioEngine : public core::Base {
    public:

        AudioEngine();

        ~AudioEngine() = default;

        bool initialize();

        bool release();

        AudioPlayer* createAudioPlayer(core::String playerName = "");

    };

}