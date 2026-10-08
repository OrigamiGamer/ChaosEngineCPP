#include "Engine/Include/Audio/AudioEngine.h"

#include "Engine/Include/Core/String.h"
#include "Engine/Include/Audio/AudioPlayer.h"

#include "Drivers/Include/Audio/OpenAL/Device.h"
#include "Drivers/Include/Audio/OpenAL/Context.h"
#include "Drivers/Include/Audio/OpenAL/Buffer.h"

namespace chaos::audio {

    AudioEngine::AudioEngine()
    {

    }

    bool AudioEngine::initialize()
    {
        // complete usage process
        openal::Device device;
        openal::Context* context = device.createContext();
        openal::Buffer* buffer = context->createBuffer();


    }

    bool AudioEngine::release()
    {

    }

    AudioPlayer* AudioEngine::createAudioPlayer(core::String playerName)
    {

    }

}