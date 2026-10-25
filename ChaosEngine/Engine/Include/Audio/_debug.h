#include "Drivers/Include/Audio/OpenAL/Device.h"
#include "Drivers/Include/Audio/OpenAL/Context.h"
#include "Drivers/Include/Audio/OpenAL/Buffer.h"
#include "Drivers/Include/Audio/OpenAL/Source.h"

#include "Engine/Include/Core/HandleMap.h"
#include "Engine/Include/Core/String.h"

#include <iostream>

namespace debug {

    using namespace chaos;

    void debug()
    {
        // complete usage process
        audio::openal::Device device;
        audio::openal::Context* context = nullptr;
        audio::openal::Buffer* buffer = nullptr;
        device.open();  // failed to open device
        context = device.createContext();
        buffer = context->createBuffer();


        core::HandleMap<core::String> map;
        core::Handle<core::String> handle = map.insert(std::make_unique<core::String>());
        *map.get(handle) = "test";
        std::cout << map.get(handle)->data() << std::endl;
        map.remove(handle);

        

    }

}
