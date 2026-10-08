#include "Drivers/Include/Audio/OpenAL/Buffer.h"

#include "Drivers/Include/Audio/OpenAL/Context.h"

namespace chaos::audio::openal {


    Buffer::Buffer()
    {

    }


    Buffer::~Buffer()
    {
        this->destroy();
    }


    bool Buffer::_makeCurrent() const
    {
        if (!this->_context) return false;

        return this->_context->makeCurrent();
    }


    bool Buffer::destroy()
    {
        if (!this->_buffer) return false;
        if (!this->_makeCurrent()) return false;

        alDeleteBuffers(1, &this->_buffer);
        this->_buffer = 0;
        return true;
    }


    bool Buffer::isValid() const
    {
        return this->_buffer != 0;
    }


    bool Buffer::setData(ALenum format, const void* data, ALsizei size, ALsizei frequency)
    {
        if (!this->_buffer) return false;
        if (!data) return false;
        if (size <= 0) return false;
        if (frequency <= 0) return false;
        if (!this->_makeCurrent()) return false;

        alBufferData(this->_buffer, format, data, size, frequency);
        return true;
    }


    ALint Buffer::getInteger(ALenum param) const
    {
        if (!this->_buffer) return 0;
        if (!this->_makeCurrent()) return 0;

        ALint value = 0;
        alGetBufferi(this->_buffer, param, &value);
        return value;
    }


    ALuint Buffer::handle() const
    {
        return this->_buffer;
    }


}
