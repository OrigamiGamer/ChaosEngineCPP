#include "Drivers/Include/Audio/OpenAL/Listener.h"

#include "Drivers/Include/Audio/OpenAL/Context.h"

namespace chaos::audio::openal {


    Listener::Listener(Context& context)
    {
        this->_context = &context;
    }


    bool Listener::setGain(ALfloat gain)
    {
        if (!this->_context) return false;
        if (!this->_context->makeCurrent()) return false;

        alListenerf(AL_GAIN, gain);
        return true;
    }


    ALfloat Listener::getGain() const
    {
        if (!this->_context) return 0.0f;
        if (!this->_context->makeCurrent()) return 0.0f;

        ALfloat value = 0.0f;
        alGetListenerf(AL_GAIN, &value);
        return value;
    }


    bool Listener::setPosition(ALfloat x, ALfloat y, ALfloat z)
    {
        if (!this->_context) return false;
        if (!this->_context->makeCurrent()) return false;

        alListener3f(AL_POSITION, x, y, z);
        return true;
    }


    bool Listener::getPosition(ALfloat& x, ALfloat& y, ALfloat& z) const
    {
        if (!this->_context) return false;
        if (!this->_context->makeCurrent()) return false;

        alGetListener3f(AL_POSITION, &x, &y, &z);
        return true;
    }


    bool Listener::setVelocity(ALfloat x, ALfloat y, ALfloat z)
    {
        if (!this->_context) return false;
        if (!this->_context->makeCurrent()) return false;

        alListener3f(AL_VELOCITY, x, y, z);
        return true;
    }


    bool Listener::getVelocity(ALfloat& x, ALfloat& y, ALfloat& z) const
    {
        if (!this->_context) return false;
        if (!this->_context->makeCurrent()) return false;

        alGetListener3f(AL_VELOCITY, &x, &y, &z);
        return true;
    }


    bool Listener::setOrientation(const ALfloat values[6])
    {
        if (!this->_context) return false;
        if (!values) return false;
        if (!this->_context->makeCurrent()) return false;

        alListenerfv(AL_ORIENTATION, values);
        return true;
    }


    bool Listener::getOrientation(ALfloat values[6]) const
    {
        if (!this->_context) return false;
        if (!values) return false;
        if (!this->_context->makeCurrent()) return false;

        alGetListenerfv(AL_ORIENTATION, values);
        return true;
    }


}
