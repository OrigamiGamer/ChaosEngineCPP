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
        // release sources
        for (auto& _source : this->sources) {
            alDeleteSources(1, &_source->_sourceID);
            delete _source;
        }
        this->sources.clear();

        // release buffers
        for (auto& _buffer : this->buffers) {
            alDeleteBuffers(1, &_buffer->_bufferID);
            delete _buffer;
        }
        this->buffers.clear();

        // release devices
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

        // generate and initialize source
        alGenSources(1, &_new_source->_sourceID);
        _new_source->_audioEngine = this;
        _new_source->name = new_sourceName;

        return _new_source;
    }



    Buffer* AudioEngine::loadAudioFile(std::string filename, std::string new_bufferName)
    {
        // get information of audio file
        SF_INFO info;
        SNDFILE* file = sf_open(filename.c_str(), SFM_READ, &info);
        if (!file) return nullptr;  // failed to open the file

        // read data from file
        sf_count_t size = info.frames * info.channels;
        std::vector<short> buf(size);
        sf_read_short(file, buf.data(), size);
        sf_close(file);

        // infer the format
        ALenum format = (info.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

        // allocate memory
        this->buffers.resize(this->buffers.size() + 1, new Buffer());
        auto& _new_buffer = this->buffers.back();

        // set default name if target name is empty
        if (new_bufferName == "") new_bufferName = "Buffer " + std::to_string(this->buffers.size());

        // generate and initialize buffer
        alGenBuffers(1, &_new_buffer->_bufferID);
        alBufferData(_new_buffer->_bufferID, format, buf.data(), static_cast<ALsizei>(size * sizeof(short)), info.samplerate);
        _new_buffer->_audioEngine = this;
        _new_buffer->name = new_bufferName;

        return _new_buffer;
    }



}