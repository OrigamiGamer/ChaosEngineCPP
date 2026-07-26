#pragma once

#include "Dependences/Include/al/al.h"
#include "Buffer.h"

#include <string>

namespace chaos::drivers::audio::openal {
    class AudioPlayer;
}

namespace chaos::drivers::audio::openal {

    class Source {
    private:
        AudioPlayer* _audioPlayer = nullptr;
        ALuint _sourceID = 0;

        inline bool _makeCurrent();

    public:
        std::string name;

        Source();

        bool pushBuffer(Buffer* in_buffer);
        bool pushBuffer(std::string bufferName);

        bool popBuffer(Buffer* target_buffer);
        bool popBuffer(std::string bufferName);

        // Play, replay, or resume this source.
        bool play();

        bool pause();

        bool stop();

        bool setVolume(float in_volume);

        bool setPositionOffset(int in_position);

        // @param in_time Units: seconds
        bool setTimeOffset(float in_time);

        // Get the volume of this source.
        // @return If failed, return 0.0.
        float getVolume();

        // Get current position offset.
        // @return If failed, return -1.
        int getPositionOffset();

        /*

        Get current time offset.
        Units: seconds
        @return If failed, return -1.0.
        */
        float getTimeOffset();


        friend class Buffer;
        friend class AudioEngine;
        friend class AudioPlayer;
    };

}