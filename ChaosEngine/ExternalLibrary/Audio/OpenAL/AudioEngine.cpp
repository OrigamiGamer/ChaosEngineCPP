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
        this->_device = alcOpenDevice(nullptr);
        if (!this->_device) return false;

        this->_context = alcCreateContext(this->_device, nullptr);
        if (!this->_context) return false;

        alcMakeContextCurrent(this->_context);

        return true;
    }



    bool AudioEngine::release()
    {
        for (auto& _source : this->sources) alDeleteSources(1, &_source->_sourceID);
        this->sources.clear();

        if (this->_context) alcDestroyContext(this->_context);
        return alcCloseDevice(this->_device);
    }



    Source* AudioEngine::createSource(std::string new_sourceName)
    {
        if (!this->_context) return nullptr;

        // allocate memory
        this->sources.resize(this->sources.size() + 1, new Source());
        auto& _new_source = this->sources.back();

        // set default name if target name is empty
        if (new_sourceName == "") new_sourceName = "Source " + std::to_string(this->sources.size());

        // initialize and generate source
        _new_source->_audioEngine = this;
        _new_source->name = new_sourceName;
        alGenSources(1, &_new_source->_sourceID);

        return _new_source;
    }



}