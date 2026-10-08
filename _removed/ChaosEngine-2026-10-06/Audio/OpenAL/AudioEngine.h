#pragma once

#include "Engine/Include/Audio/IAudioEngine.h"

#include "Engine/Include/Core/String.h"

#include <vector>

struct ALCdevice;

namespace chaos::audio::openal {
    class AudioPlayer;
}

namespace chaos::audio::openal {

    class AudioEngine {
    private:
        ALCdevice* _device = nullptr;

    public:
        std::vector<AudioPlayer*> audioPlayers;

        AudioEngine();

        bool initialize();

        bool release();

        IAudioPlayer* createAudioPlayer(core::String playerName = "");

        friend class Buffer;
        friend class AudioPlayer;
        friend class Source;
    };

}