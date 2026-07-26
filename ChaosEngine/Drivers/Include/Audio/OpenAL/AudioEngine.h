#pragma once

#include "Dependences/Include/al/alc.h"

#include <vector>
#include <string>

namespace chaos::drivers::audio::openal {
    class AudioPlayer;
}

namespace chaos::drivers::audio::openal {

    class AudioEngine {
    private:
        ALCdevice* _device = nullptr;

    public:
        std::vector<AudioPlayer*> audioPlayers;

        AudioEngine();

        int getLastError();

        bool initialize();

        bool release();

        AudioPlayer* createAudioPlayer(std::string in_playerName = "");

        friend class Buffer;
        friend class AudioPlayer;
        friend class Source;
    };

}