#pragma once

#include "Drivers/Audio/OpenAL/Include/Source.h"

#include "Drivers/Audio/OpenAL/Include/AudioPlayer.h"
#include "Dependences/Include/al/alc.h"

namespace chaos::drivers::audio::openal {


    Source::Source()
    {

    }


    inline bool Source::_makeCurrent()
    {
        if (!this->_audioPlayer) return false;
        if (!this->_audioPlayer->_context) return false;
        alcMakeContextCurrent(this->_audioPlayer->_context);
        return true;
    }


    bool Source::pushBuffer(Buffer* in_buffer)
    {
        if (!this->_makeCurrent()) return false;

        if (this->_sourceID == 0) return false;
        if (!in_buffer) return false;
        if (in_buffer->_bufferID == 0) return false;
        alSourceQueueBuffers(this->_sourceID, 1, &in_buffer->_bufferID);
        return true;
    }


    bool Source::pushBuffer(std::string bufferName)
    {
        if (!this->_makeCurrent()) return false;

        if (bufferName.empty()) return false;

        for (auto& buffer : this->_audioPlayer->buffers) {
            if (buffer->name == bufferName) {
                alSourceQueueBuffers(this->_sourceID, 1, &buffer->_bufferID);
                return true;
            }
        }
        return false;
    }


    bool Source::popBuffer(Buffer* target_buffer)
    {
        if (!this->_makeCurrent()) return false;

        if (this->_sourceID == 0) return false;
        if (!target_buffer) return false;
        if (target_buffer->_bufferID == 0) return false;
        alSourceUnqueueBuffers(this->_sourceID, 1, &target_buffer->_bufferID);
        return true;
    }


    bool Source::popBuffer(std::string bufferName)
    {
        if (!this->_makeCurrent()) return false;

        if (bufferName.empty()) return false;

        if (this->_sourceID == 0) return false;
        for (auto& buffer : this->_audioPlayer->buffers) {
            if (buffer->name == bufferName) {
                alSourceUnqueueBuffers(this->_sourceID, 1, &buffer->_bufferID);
                return true;
            }
        }
        return false;
    }


    bool Source::play()
    {
        if (!this->_makeCurrent()) return false;

        if (this->_sourceID == 0) return false;
        alSourcePlay(this->_sourceID);
        return true;
    }


    bool Source::pause()
    {
        if (!this->_makeCurrent()) return false;

        if (this->_sourceID == 0) return false;
        alSourcePause(this->_sourceID);
        return true;
    }


    bool Source::stop()
    {
        if (!this->_makeCurrent()) return false;

        if (this->_sourceID == 0) return false;
        alSourceStop(this->_sourceID);
        return true;
    }


    bool Source::setVolume(float in_volume)
    {
        if (!this->_makeCurrent()) return false;

        // correct volume
        if (in_volume < 0) in_volume = 0.0f;
        if (in_volume > 1) in_volume = 1.0f;

        if (this->_sourceID == 0) return false;
        alSourcef(this->_sourceID, AL_GAIN, in_volume);
        return true;
    }


    bool Source::setPositionOffset(int in_position)
    {
        if (!this->_makeCurrent()) return false;

        // correct offset
        if (in_position < 0) in_position = 0;
        // if(in_offset > what) in_offset = what;

        if (this->_sourceID == 0) return false;
        alSourcei(this->_sourceID, AL_SAMPLE_OFFSET, in_position);
        return true;
    }


    bool Source::setTimeOffset(float in_time)
    {
        if (!this->_makeCurrent()) return false;

        // correct offset
        if (in_time < 0) in_time = 0;
        // if(in_offset > what) in_offset = what;

        if (this->_sourceID == 0) return false;
        alSourcef(this->_sourceID, AL_SEC_OFFSET, in_time);
        return true;
    }


    float Source::getVolume()
    {
        if (!this->_makeCurrent()) return 0.0f;

        if (this->_sourceID == 0) return 0.0f;
        ALfloat _volume = 0.0f;
        alGetSourcef(this->_sourceID, AL_GAIN, &_volume);
        return _volume;
    }


    int Source::getPositionOffset()
    {
        if (!this->_makeCurrent()) return -1;

        if (this->_sourceID == 0) return -1;
        ALint _pos = -1;
        alGetSourcei(this->_sourceID, AL_SAMPLE_OFFSET, &_pos);
        return _pos;
    }


    float Source::getTimeOffset()
    {
        if (!this->_makeCurrent()) return -1.0f;

        if (this->_sourceID == 0);
        ALfloat _time = -1.0f;
        alGetSourcef(this->_sourceID, AL_SEC_OFFSET, &_time);
        return _time;
    }


}