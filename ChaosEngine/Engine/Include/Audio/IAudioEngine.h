#pragma once

#include <string>

namespace chaos::audio {
    class IAudioPlayer;
}

namespace chaos::audio {

    class IAudioEngine {
    public:

        virtual ~IAudioEngine() = default;

        virtual bool initialize() = 0;

        virtual bool release() = 0;

        virtual IAudioPlayer* createAudioPlayer(std::string playerName = "") = 0;
    };

}