#pragma once

#include "Dependences/Include/al/al.h"

#include <string>

namespace chaos::audio::openal {
    class AudioPlayer;
}

namespace chaos::audio::openal {

    class Buffer {
    private:
        AudioPlayer* _audioPlayer = nullptr;
        ALuint _bufferID = 0;

    public:
        std::string name;

        Buffer();

        friend class AudioEngine;
        friend class AudioPlayer;
        friend class Source;
    };

}