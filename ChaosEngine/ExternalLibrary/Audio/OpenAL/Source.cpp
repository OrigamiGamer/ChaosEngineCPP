#pragma once

#include "ExternalLibrary/Audio/OpenAL/OpenAL.h"



namespace OpenAL {



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



    bool Source::pushBuffer(Buffer* new_buffer)
    {
        if (!this->_makeCurrent()) return false;

        if (this->_sourceID == 0) return false;
        if (!new_buffer) return false;
        if (new_buffer->_bufferID == 0) return false;
        alSourceQueueBuffers(this->_sourceID, 1, &new_buffer->_bufferID);

        return true;
    }



    bool Source::pushBuffer(std::string bufferName)
    {
        if (!this->_makeCurrent()) return false;

        if (bufferName.empty() || bufferName == "") return false;

        for (auto& buffer : this->_audioPlayer->buffers) {
            if (buffer->name == bufferName) {
                this->pushBuffer(buffer);
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



    bool Source::setVolume(float new_volume)
    {
        if (!this->_makeCurrent()) return false;

        // correct volume
        if (new_volume < 0) new_volume = 0.0f;
        if (new_volume > 1) new_volume = 1.0f;

        if (this->_sourceID == 0) return false;
        alSourcef(this->_sourceID, AL_GAIN, new_volume);

        return true;
    }



    bool Source::setPositionOffset(int new_position)
    {
        if (!this->_makeCurrent()) return false;

        // correct offset
        if (new_position < 0) new_position = 0;
        // if(new_offset > what) new_offset = what;

        if (this->_sourceID == 0) return false;
        alSourcei(this->_sourceID, AL_SAMPLE_OFFSET, new_position);

        return true;
    }



    bool Source::setTimeOffset(float new_time)
    {
        if (!this->_makeCurrent()) return false;

        // correct offset
        if (new_time < 0) new_time = 0;
        // if(new_offset > what) new_offset = what;

        if (this->_sourceID == 0) return false;
        alSourcef(this->_sourceID, AL_SEC_OFFSET, new_time);

        return true;
    }



}