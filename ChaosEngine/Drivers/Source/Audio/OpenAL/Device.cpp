#include "Drivers/Include/Audio/OpenAL/Device.h"

#include "Drivers/Include/Audio/OpenAL/Context.h"

namespace chaos::audio::openal {


    Device::Device()
    {

    }


    Device::~Device()
    {
        close();
    }


    Device::Device(Device&& other) noexcept
        : _device(other._device), _contexts(std::move(other._contexts))
    {
        other._device = nullptr;
    }


    ALCdevice* Device::handle() const
    {
        return _device;
    }


    Device& Device::operator=(Device&& other) noexcept
    {
        if (this != &other)
        {
            close();
            _device = other._device;
            _contexts = std::move(other._contexts);
            other._device = nullptr;
        }
        return *this;
    }


    bool Device::open(const char* deviceName)
    {
        if (_device) return false;

        _device = alcOpenDevice(deviceName);
        if (!_device) return false;

        return true;
    }


    bool Device::close()
    {
        if (!_device) return false;

        for (auto* context : _contexts) delete context;
        _contexts.clear();

        if (!alcCloseDevice(_device)) return false;
        _device = nullptr;
        return true;
    }


    bool Device::isOpen() const
    {
        return _device != nullptr;
    }


    Context* Device::createContext(const ALCint* attributes)
    {
        if (!_device) return nullptr;

        Context* context = new Context();
        if (!context->create(*this, attributes))
        {
            delete context;
            return nullptr;
        }

        _contexts.push_back(context);
        return context;
    }


}
