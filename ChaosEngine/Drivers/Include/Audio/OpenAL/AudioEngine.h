#pragma once

#include "Engine/Include/Audio/IAudioEngine.h"

#include "Engine/Include/Core/String.h"

#include <vector>

struct ALCdevice;

namespace chaos::audio::openal {
    class AudioPlayer;
}

namespace chaos::audio::openal {

    class AudioEngine final : public chaos::audio::IAudioEngine {
    private:
        ALCdevice* _device = nullptr;

    public:
        std::vector<AudioPlayer*> audioPlayers;

        AudioEngine();

        bool initialize() override;

        bool release() override;

        IAudioPlayer* createAudioPlayer(core::String playerName = "") override;

        friend class Buffer;
        friend class AudioPlayer;
        friend class Source;
    };

}