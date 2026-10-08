#include "Drivers/Include/Audio/OpenAL/Context.h"

#include "Drivers/Include/Audio/OpenAL/Buffer.h"
#include "Drivers/Include/Audio/OpenAL/Source.h"
#include "Drivers/Include/Audio/OpenAL/Listener.h"
#include "Drivers/Include/Audio/OpenAL/Device.h"
#include "Dependences/Include/al/al.h"

namespace chaos::audio::openal {


    Context::Context()
    {

    }


    Context::~Context()
    {
        this->destroy();
    }


    Context::Context(Context&& other) noexcept
        : _context(other._context),
          _buffers(std::move(other._buffers)),
          _sources(std::move(other._sources)),
          _listeners(std::move(other._listeners))
    {
        other._context = nullptr;

        for (auto* buffer : this->_buffers) buffer->_context = this;
        for (auto* source : this->_sources) source->_context = this;
        for (auto* listener : this->_listeners) listener->_context = this;
    }


    Context& Context::operator=(Context&& other) noexcept
    {
        if (this != &other)
        {
            this->destroy();

            this->_context = other._context;
            this->_buffers = std::move(other._buffers);
            this->_sources = std::move(other._sources);
            this->_listeners = std::move(other._listeners);

            other._context = nullptr;

            for (auto* buffer : this->_buffers) buffer->_context = this;
            for (auto* source : this->_sources) source->_context = this;
            for (auto* listener : this->_listeners) listener->_context = this;
        }
        return *this;
    }


    bool Context::create(Device& device, const ALCint* attributes)
    {
        if (this->_context) return false;
        if (!device.handle()) return false;

        this->_context = alcCreateContext(device.handle(), attributes);
        if (!this->_context) return false;

        return true;
    }


    Buffer* Context::createBuffer()
    {
        if (!this->_context) return nullptr;
        if (!this->makeCurrent()) return nullptr;

        Buffer* buffer = new Buffer();
        buffer->_context = this;
        alGenBuffers(1, &buffer->_buffer);
        if (!buffer->_buffer)
        {
            delete buffer;
            return nullptr;
        }

        this->_buffers.push_back(buffer);
        return buffer;
    }


    Source* Context::createSource()
    {
        if (!this->_context) return nullptr;
        if (!this->makeCurrent()) return nullptr;

        Source* source = new Source();
        source->_context = this;
        alGenSources(1, &source->_source);
        if (!source->_source)
        {
            delete source;
            return nullptr;
        }

        this->_sources.push_back(source);
        return source;
    }


    Listener* Context::createListener()
    {
        if (!this->_context) return nullptr;

        Listener* listener = new Listener(*this);

        this->_listeners.push_back(listener);
        return listener;
    }


    bool Context::destroy()
    {
        if (!this->_context) return false;

        this->makeCurrent();

        for (auto* listener : this->_listeners) delete listener;
        this->_listeners.clear();

        for (auto* source : this->_sources) delete source;
        this->_sources.clear();

        for (auto* buffer : this->_buffers) delete buffer;
        this->_buffers.clear();

        if (alcGetCurrentContext() == this->_context)
            alcMakeContextCurrent(nullptr);

        alcDestroyContext(this->_context);
        this->_context = nullptr;
        return true;
    }


    bool Context::isValid() const
    {
        return this->_context != nullptr;
    }


    bool Context::makeCurrent()
    {
        if (!this->_context) return false;

        return alcMakeContextCurrent(this->_context) == ALC_TRUE;
    }


    bool Context::makeNoneCurrent()
    {
        return alcMakeContextCurrent(nullptr) == ALC_TRUE;
    }


    void Context::suspend()
    {
        if (!this->_context) return;

        alcSuspendContext(this->_context);
    }


    void Context::process()
    {
        if (!this->_context) return;

        alcProcessContext(this->_context);
    }


    ALCcontext* Context::handle() const
    {
        return this->_context;
    }


}
