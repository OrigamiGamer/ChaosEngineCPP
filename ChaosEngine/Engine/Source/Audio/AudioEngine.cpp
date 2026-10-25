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
        return true;
    }

    bool AudioEngine::release()
    {
        return true;
    }

    AudioPlayer* AudioEngine::createAudioPlayer(core::String playerName)
    {
        return nullptr;
    }

}