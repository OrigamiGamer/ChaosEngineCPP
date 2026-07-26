#include "Drivers/Include/Audio/OpenAL/AudioEngine.h"

#include "Drivers/Include/Audio/OpenAL/AudioPlayer.h"
#include "Dependences/Include/al/al.h"
#include "Dependences/Include/al/alc.h"

namespace chaos::audio::openal {


    AudioEngine::AudioEngine()
    {

    }


    bool AudioEngine::initialize()
    {
        if (this->_device) return false;

        this->_device = alcOpenDevice(nullptr);
        if (!this->_device) return false;

        return true;
    }


    bool AudioEngine::release()
    {
        if (!this->_device) return false;

        // release audio players
        for (auto& _player : this->audioPlayers) {
            _player->_release();
            delete _player;
        }
        this->audioPlayers.clear();

        return alcCloseDevice(this->_device);
    }


    IAudioPlayer* AudioEngine::createAudioPlayer(std::string playerName)
    {
        if (!this->_device) return nullptr;

        size_t in_size = this->audioPlayers.size() + 1;

        // set default name if target name is empty
        if (playerName == "") playerName = "AudioPlayer " + std::to_string(in_size);
        else for (auto& _player : this->audioPlayers) {
            if (_player->name == playerName) return nullptr;    // the audio player with this name has already existed
        }

        // allocate memory
        this->audioPlayers.resize(in_size, new AudioPlayer());
        auto& _in_player = this->audioPlayers.back();

        // create and initialize audio player
        _in_player->_audioEngine = this;
        _in_player->name = playerName;
        if (!_in_player->_initialize()) return nullptr;

        return _in_player;
    }


}