#pragma once

#include "Drivers/Audio/OpenAL/Include/AudioEngine.h"

#include "Drivers/Audio/OpenAL/Include/AudioPlayer.h"
#include "Dependences/Include/al/al.h"

namespace chaos::drivers::audio::openal {


    AudioEngine::AudioEngine()
    {

    }


    int AudioEngine::getLastError()
    {
        return alGetError();
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


    AudioPlayer* AudioEngine::createAudioPlayer(std::string in_playerName)
    {
        if (!this->_device) return nullptr;

        size_t in_size = this->audioPlayers.size() + 1;

        // set default name if target name is empty
        if (in_playerName == "") in_playerName = "AudioPlayer " + std::to_string(in_size);
        else for (auto& _player : this->audioPlayers) {
            if (_player->name == in_playerName) return nullptr;    // the audio player with this name has already existed
        }

        // allocate memory
        this->audioPlayers.resize(in_size, new AudioPlayer());
        auto& _in_player = this->audioPlayers.back();

        // create and initialize audio player
        _in_player->_audioEngine = this;
        _in_player->name = in_playerName;
        if (!_in_player->_initialize()) return nullptr;

        return _in_player;
    }


}