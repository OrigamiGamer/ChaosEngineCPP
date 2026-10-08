#pragma once

#include "Dependences/Include/al/al.h"
#include "Engine/Include/Audio/IBuffer.h"

#include <string>

namespace chaos::audio::openal {
    class AudioPlayer;
}

namespace chaos::audio::openal {

    class Buffer : public IBuffer {
    private:
        AudioPlayer* _audioPlayer = nullptr;
        ALuint _bufferID = 0;

    public:

        Buffer();

        friend class Device;
        friend class AudioPlayer;
        friend class Source;
    };

}