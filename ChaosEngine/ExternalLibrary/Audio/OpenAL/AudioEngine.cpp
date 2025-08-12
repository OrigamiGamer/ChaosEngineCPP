#pragma once

#include "ExternalLibrary/Audio/OpenAL/OpenAL.h"



namespace OpenAL {



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



    AudioPlayer* AudioEngine::createAudioPlayer(std::string new_playerName)
    {
        if (!this->_device) return nullptr;

        size_t new_size = this->audioPlayers.size() + 1;

        // set default name if target name is empty
        if (new_playerName == "") new_playerName = "AudioPlayer " + std::to_string(new_size);
        else for (auto& _player : this->audioPlayers) {
            if (_player->name == new_playerName) return nullptr;    // the audio player with this name has already existed
        }

        // allocate memory
        this->audioPlayers.resize(new_size, new AudioPlayer());
        auto& _new_player = this->audioPlayers.back();

        // create and initialize audio player
        _new_player->_audioEngine = this;
        _new_player->name = new_playerName;
        if (!_new_player->_initialize()) return nullptr;

        return _new_player;
    }



}