#include "Drivers/Include/Audio/OpenAL/Source.h"

#include "Drivers/Include/Audio/OpenAL/Buffer.h"
#include "Drivers/Include/Audio/OpenAL/Context.h"

namespace chaos::audio::openal {


    Source::Source()
    {

    }


    Source::~Source()
    {
        this->destroy();
    }


    bool Source::_makeCurrent() const
    {
        if (!this->_context) return false;

        return this->_context->makeCurrent();
    }


    bool Source::destroy()
    {
        if (!this->_source) return false;
        if (!this->_makeCurrent()) return false;

        alDeleteSources(1, &this->_source);
        this->_source = 0;
        return true;
    }


    bool Source::isValid() const
    {
        return this->_source != 0;
    }


    bool Source::play()
    {
        if (!this->_source) return false;
        if (!this->_makeCurrent()) return false;

        alSourcePlay(this->_source);
        return true;
    }


    bool Source::pause()
    {
        if (!this->_source) return false;
        if (!this->_makeCurrent()) return false;

        alSourcePause(this->_source);
        return true;
    }


    bool Source::stop()
    {
        if (!this->_source) return false;
        if (!this->_makeCurrent()) return false;

        alSourceStop(this->_source);
        return true;
    }


    bool Source::rewind()
    {
        if (!this->_source) return false;
        if (!this->_makeCurrent()) return false;

        alSourceRewind(this->_source);
        return true;
    }


    ALenum Source::state() const
    {
        if (!this->_source) return 0;
        if (!this->_makeCurrent()) return 0;

        ALint value = 0;
        alGetSourcei(this->_source, AL_SOURCE_STATE, &value);
        return value;
    }


    bool Source::queueBuffers(const ALuint* bufferIds, ALsizei count)
    {
        if (!this->_source) return false;
        if (!bufferIds) return false;
        if (count <= 0) return false;
        if (!this->_makeCurrent()) return false;

        alSourceQueueBuffers(this->_source, count, bufferIds);
        return true;
    }


    bool Source::unqueueBuffers(ALuint* bufferIds, ALsizei count)
    {
        if (!this->_source) return false;
        if (!bufferIds) return false;
        if (count <= 0) return false;
        if (!this->_makeCurrent()) return false;

        alSourceUnqueueBuffers(this->_source, count, bufferIds);
        return true;
    }


    ALint Source::queuedBufferCount() const
    {
        if (!this->_source) return 0;
        if (!this->_makeCurrent()) return 0;

        ALint value = 0;
        alGetSourcei(this->_source, AL_BUFFERS_QUEUED, &value);
        return value;
    }


    ALint Source::processedBufferCount() const
    {
        if (!this->_source) return 0;
        if (!this->_makeCurrent()) return 0;

        ALint value = 0;
        alGetSourcei(this->_source, AL_BUFFERS_PROCESSED, &value);
        return value;
    }


    bool Source::setBuffer(const Buffer& buffer)
    {
        if (!this->_source) return false;
        if (!buffer.handle()) return false;
        if (!this->_makeCurrent()) return false;

        alSourcei(this->_source, AL_BUFFER, static_cast<ALint>(buffer.handle()));
        return true;
    }


    bool Source::detachBuffer()
    {
        if (!this->_source) return false;
        if (!this->_makeCurrent()) return false;

        alSourcei(this->_source, AL_BUFFER, 0);
        return true;
    }


    bool Source::setGain(ALfloat gain)
    {
        if (!this->_source) return false;
        if (!this->_makeCurrent()) return false;

        alSourcef(this->_source, AL_GAIN, gain);
        return true;
    }


    ALfloat Source::getGain() const
    {
        if (!this->_source) return 0.0f;
        if (!this->_makeCurrent()) return 0.0f;

        ALfloat value = 0.0f;
        alGetSourcef(this->_source, AL_GAIN, &value);
        return value;
    }


    bool Source::setPitch(ALfloat pitch)
    {
        if (!this->_source) return false;
        if (!this->_makeCurrent()) return false;

        alSourcef(this->_source, AL_PITCH, pitch);
        return true;
    }


    ALfloat Source::getPitch() const
    {
        if (!this->_source) return 0.0f;
        if (!this->_makeCurrent()) return 0.0f;

        ALfloat value = 0.0f;
        alGetSourcef(this->_source, AL_PITCH, &value);
        return value;
    }


    bool Source::setLooping(ALboolean looping)
    {
        if (!this->_source) return false;
        if (!this->_makeCurrent()) return false;

        alSourcei(this->_source, AL_LOOPING, looping);
        return true;
    }


    bool Source::setTimeOffset(ALfloat seconds)
    {
        if (!this->_source) return false;
        if (!this->_makeCurrent()) return false;

        alSourcef(this->_source, AL_SEC_OFFSET, seconds);
        return true;
    }


    ALfloat Source::getTimeOffset() const
    {
        if (!this->_source) return -1.0f;
        if (!this->_makeCurrent()) return -1.0f;

        ALfloat value = -1.0f;
        alGetSourcef(this->_source, AL_SEC_OFFSET, &value);
        return value;
    }


    bool Source::setSampleOffset(ALint samples)
    {
        if (!this->_source) return false;
        if (!this->_makeCurrent()) return false;

        alSourcei(this->_source, AL_SAMPLE_OFFSET, samples);
        return true;
    }


    ALint Source::getSampleOffset() const
    {
        if (!this->_source) return -1;
        if (!this->_makeCurrent()) return -1;

        ALint value = -1;
        alGetSourcei(this->_source, AL_SAMPLE_OFFSET, &value);
        return value;
    }


    bool Source::setPosition(ALfloat x, ALfloat y, ALfloat z)
    {
        if (!this->_source) return false;
        if (!this->_makeCurrent()) return false;

        alSource3f(this->_source, AL_POSITION, x, y, z);
        return true;
    }


    ALuint Source::handle() const
    {
        return this->_source;
    }


}
