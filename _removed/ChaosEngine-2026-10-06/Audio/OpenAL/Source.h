#pragma once

#include "Dependences/Include/al/al.h"
#include "Buffer.h"

#include "Engine/Include/Core/String.h"
#include "Engine/Include/Audio/ISource.h"

namespace chaos::audio::openal {
    class AudioPlayer;
}

namespace chaos::audio::openal {

    class Source {
    private:
        AudioPlayer* _audioPlayer = nullptr;
        ALuint _sourceID = 0;

        inline bool _makeCurrent();

    public:

        Source();

        bool pushBuffer(Buffer* in_buffer);
        bool pushBuffer(core::String bufferName);

        bool popBuffer(Buffer* target_buffer);
        bool popBuffer(core::String bufferName);

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
        friend class Device;
        friend class AudioPlayer;
    };

}