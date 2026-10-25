#include "Drivers/Include/Audio/OpenAL/Source.h"

#include "Drivers/Include/Audio/OpenAL/Buffer.h"
#include "Drivers/Include/Audio/OpenAL/Context.h"

namespace chaos::audio::openal {


    Source::Source()
    {

    }


    Source::~Source()
    {
        destroy();
    }


    bool Source::makeCurrent() const
    {
        if (!_context) return false;

        return _context->makeCurrent();
    }


    ALuint Source::handle() const
    {
        return _source;
    }


    bool Source::destroy()
    {
        if (!_source) return false;
        if (!makeCurrent()) return false;

        alDeleteSources(1, &_source);
        _source = 0;
        return true;
    }


    bool Source::isValid() const
    {
        return _source != 0;
    }


    bool Source::play()
    {
        if (!_source) return false;
        if (!makeCurrent()) return false;

        alSourcePlay(_source);
        return true;
    }


    bool Source::pause()
    {
        if (!_source) return false;
        if (!makeCurrent()) return false;

        alSourcePause(_source);
        return true;
    }


    bool Source::stop()
    {
        if (!_source) return false;
        if (!makeCurrent()) return false;

        alSourceStop(_source);
        return true;
    }


    bool Source::rewind()
    {
        if (!_source) return false;
        if (!makeCurrent()) return false;

        alSourceRewind(_source);
        return true;
    }


    ALenum Source::state() const
    {
        if (!_source) return 0;
        if (!makeCurrent()) return 0;

        ALint value = 0;
        alGetSourcei(_source, AL_SOURCE_STATE, &value);
        return value;
    }


    bool Source::queueBuffers(const ALuint* bufferIds, ALsizei count)
    {
        if (!_source) return false;
        if (!bufferIds) return false;
        if (count <= 0) return false;
        if (!makeCurrent()) return false;

        alSourceQueueBuffers(_source, count, bufferIds);
        return true;
    }


    bool Source::unqueueBuffers(ALuint* bufferIds, ALsizei count)
    {
        if (!_source) return false;
        if (!bufferIds) return false;
        if (count <= 0) return false;
        if (!makeCurrent()) return false;

        alSourceUnqueueBuffers(_source, count, bufferIds);
        return true;
    }


    ALint Source::queuedBufferCount() const
    {
        if (!_source) return 0;
        if (!makeCurrent()) return 0;

        ALint value = 0;
        alGetSourcei(_source, AL_BUFFERS_QUEUED, &value);
        return value;
    }


    ALint Source::processedBufferCount() const
    {
        if (!_source) return 0;
        if (!makeCurrent()) return 0;

        ALint value = 0;
        alGetSourcei(_source, AL_BUFFERS_PROCESSED, &value);
        return value;
    }


    bool Source::setBuffer(const Buffer& buffer)
    {
        if (!_source) return false;
        if (!buffer.handle()) return false;
        if (!makeCurrent()) return false;

        alSourcei(_source, AL_BUFFER, static_cast<ALint>(buffer.handle()));
        return true;
    }


    bool Source::detachBuffer()
    {
        if (!_source) return false;
        if (!makeCurrent()) return false;

        alSourcei(_source, AL_BUFFER, 0);
        return true;
    }


    bool Source::setGain(ALfloat gain)
    {
        if (!_source) return false;
        if (!makeCurrent()) return false;

        alSourcef(_source, AL_GAIN, gain);
        return true;
    }


    ALfloat Source::getGain() const
    {
        if (!_source) return 0.0f;
        if (!makeCurrent()) return 0.0f;

        ALfloat value = 0.0f;
        alGetSourcef(_source, AL_GAIN, &value);
        return value;
    }


    bool Source::setPitch(ALfloat pitch)
    {
        if (!_source) return false;
        if (!makeCurrent()) return false;

        alSourcef(_source, AL_PITCH, pitch);
        return true;
    }


    ALfloat Source::getPitch() const
    {
        if (!_source) return 0.0f;
        if (!makeCurrent()) return 0.0f;

        ALfloat value = 0.0f;
        alGetSourcef(_source, AL_PITCH, &value);
        return value;
    }


    bool Source::setLooping(ALboolean looping)
    {
        if (!_source) return false;
        if (!makeCurrent()) return false;

        alSourcei(_source, AL_LOOPING, looping);
        return true;
    }


    bool Source::setTimeOffset(ALfloat seconds)
    {
        if (!_source) return false;
        if (!makeCurrent()) return false;

        alSourcef(_source, AL_SEC_OFFSET, seconds);
        return true;
    }


    ALfloat Source::getTimeOffset() const
    {
        if (!_source) return -1.0f;
        if (!makeCurrent()) return -1.0f;

        ALfloat value = -1.0f;
        alGetSourcef(_source, AL_SEC_OFFSET, &value);
        return value;
    }


    bool Source::setSampleOffset(ALint samples)
    {
        if (!_source) return false;
        if (!makeCurrent()) return false;

        alSourcei(_source, AL_SAMPLE_OFFSET, samples);
        return true;
    }


    ALint Source::getSampleOffset() const
    {
        if (!_source) return -1;
        if (!makeCurrent()) return -1;

        ALint value = -1;
        alGetSourcei(_source, AL_SAMPLE_OFFSET, &value);
        return value;
    }


    bool Source::setPosition(ALfloat x, ALfloat y, ALfloat z)
    {
        if (!_source) return false;
        if (!makeCurrent()) return false;

        alSource3f(_source, AL_POSITION, x, y, z);
        return true;
    }


}
