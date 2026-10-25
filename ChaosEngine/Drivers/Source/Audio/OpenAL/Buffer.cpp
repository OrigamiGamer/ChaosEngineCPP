#include "Drivers/Include/Audio/OpenAL/Buffer.h"

#include "Drivers/Include/Audio/OpenAL/Context.h"

namespace chaos::audio::openal {


    Buffer::Buffer()
    {

    }


    Buffer::~Buffer()
    {
        destroy();
    }


    bool Buffer::makeCurrent() const
    {
        if (!_context) return false;

        return _context->makeCurrent();
    }


    ALuint Buffer::handle() const
    {
        return _buffer;
    }


    bool Buffer::destroy()
    {
        if (!_buffer) return false;
        if (!makeCurrent()) return false;

        alDeleteBuffers(1, &_buffer);
        _buffer = 0;
        return true;
    }


    bool Buffer::isValid() const
    {
        return _buffer != 0;
    }


    bool Buffer::setData(ALenum format, const void* data, ALsizei size, ALsizei frequency)
    {
        if (!_buffer) return false;
        if (!data) return false;
        if (size <= 0) return false;
        if (frequency <= 0) return false;
        if (!makeCurrent()) return false;

        alBufferData(_buffer, format, data, size, frequency);
        return true;
    }


    ALint Buffer::getInteger(ALenum param) const
    {
        if (!_buffer) return 0;
        if (!makeCurrent()) return 0;

        ALint value = 0;
        alGetBufferi(_buffer, param, &value);
        return value;
    }


}
