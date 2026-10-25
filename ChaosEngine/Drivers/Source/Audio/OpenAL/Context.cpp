#include "Drivers/Include/Audio/OpenAL/Context.h"

#include "Drivers/Include/Audio/OpenAL/Buffer.h"
#include "Drivers/Include/Audio/OpenAL/Source.h"
#include "Drivers/Include/Audio/OpenAL/Listener.h"
#include "Drivers/Include/Audio/OpenAL/Device.h"
#include "Dependences/Include/al/al.h"

#include <vector>
#include <memory>

namespace chaos::audio::openal {


    Context::Context()
    {

    }


    Context::~Context()
    {
        destroy();
    }


    Context::Context(Context&& other) noexcept
        : _context(other._context),
        _buffers(std::move(other._buffers)),
        _sources(std::move(other._sources)),
        _listeners(std::move(other._listeners))
    {
        other._context = nullptr;

        for (auto& buffer : _buffers) buffer->_context = this;
        for (auto& source : _sources) source->_context = this;
        for (auto& listener : _listeners) listener->_context = this;
    }


    Context& Context::operator=(Context&& other) noexcept
    {
        if (this != &other)
        {
            destroy();

            _context = other._context;
            _buffers = std::move(other._buffers);
            _sources = std::move(other._sources);
            _listeners = std::move(other._listeners);

            other._context = nullptr;

            for (auto& buffer : _buffers) buffer->_context = this;
            for (auto& source : _sources) source->_context = this;
            for (auto& listener : _listeners) listener->_context = this;
        }
        return *this;
    }


    bool Context::create(Device& device, const ALCint* attributes)
    {
        if (_context) return false;
        if (!device.handle()) return false;

        _context = alcCreateContext(device.handle(), attributes);
        if (!_context) return false;

        return true;
    }


    Buffer* Context::createBuffer()
    {
        if (!_context) return nullptr;
        if (!makeCurrent()) return nullptr;

        _buffers.push_back(std::make_unique<Buffer>());
        auto& buffer = _buffers.back();
        buffer->_context = this;
        alGenBuffers(1, &buffer->_buffer);
        if (!buffer->_buffer)
        {
            _buffers.pop_back();
            return nullptr;
        }

        return buffer.get();    // TODO: 返回值改用 Handle<Buffer> 类型。
    }


    Source* Context::createSource()
    {
        if (!_context) return nullptr;
        if (!makeCurrent()) return nullptr;

        _sources.push_back(std::make_unique<Source>());   // problems
        auto& source = _sources.back();
        source->_context = this;
        alGenSources(1, &source->_source);
        if (!source->handle())
        {
            _sources.pop_back();
            return nullptr;
        }

        return source.get();    // TODO: 返回值改用 Handle<Source> 类型。
    }


    Listener* Context::createListener()
    {
        if (!_context) return nullptr;

        _listeners.push_back(std::make_unique<Listener>(this));
        auto& listener = _listeners.back();

        return listener.get();  // TODO: 返回值改用 Handle<Listener> 类型。
    }


    bool Context::destroy()
    {
        if (!_context) return false;

        makeCurrent();

        _listeners.clear();
        _sources.clear();
        _buffers.clear();

        if (alcGetCurrentContext() == _context)
            alcMakeContextCurrent(nullptr);

        alcDestroyContext(_context);
        _context = nullptr;
        return true;
    }


    bool Context::isValid() const
    {
        return _context != nullptr;
    }


    bool Context::makeCurrent()
    {
        if (!_context) return false;

        return alcMakeContextCurrent(_context) == ALC_TRUE;
    }


    bool Context::makeNoneCurrent()
    {
        return alcMakeContextCurrent(nullptr) == ALC_TRUE;
    }


    void Context::suspend()
    {
        if (!_context) return;

        alcSuspendContext(_context);
    }


    void Context::process()
    {
        if (!_context) return;

        alcProcessContext(_context);
    }


}
