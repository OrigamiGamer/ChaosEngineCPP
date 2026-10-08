#include "Drivers/Include/Audio/OpenAL/Device.h"

#include "Drivers/Include/Audio/OpenAL/Context.h"

namespace chaos::audio::openal {


    Device::Device()
    {

    }


    Device::~Device()
    {
        this->close();
    }


    Device::Device(Device&& other) noexcept
        : _device(other._device), _contexts(std::move(other._contexts))
    {
        other._device = nullptr;
    }


    Device& Device::operator=(Device&& other) noexcept
    {
        if (this != &other)
        {
            this->close();
            this->_device = other._device;
            this->_contexts = std::move(other._contexts);
            other._device = nullptr;
        }
        return *this;
    }


    bool Device::open(const char* deviceName)
    {
        if (this->_device) return false;

        this->_device = alcOpenDevice(deviceName);
        if (!this->_device) return false;

        return true;
    }


    bool Device::close()
    {
        if (!this->_device) return false;

        for (auto* context : this->_contexts) delete context;
        this->_contexts.clear();

        if (!alcCloseDevice(this->_device)) return false;
        this->_device = nullptr;
        return true;
    }


    bool Device::isOpen() const
    {
        return this->_device != nullptr;
    }


    Context* Device::createContext(const ALCint* attributes)
    {
        if (!this->_device) return nullptr;

        Context* context = new Context();
        if (!context->create(*this, attributes))
        {
            delete context;
            return nullptr;
        }

        this->_contexts.push_back(context);
        return context;
    }


    ALCdevice* Device::handle() const
    {
        return this->_device;
    }


}
