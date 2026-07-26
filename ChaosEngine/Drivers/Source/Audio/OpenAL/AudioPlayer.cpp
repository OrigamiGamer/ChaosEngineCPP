#include "Drivers/Include/Audio/OpenAL/AudioPlayer.h"

#include "Drivers/Include/Audio/OpenAL/Source.h"
#include "Drivers/Include/Audio/OpenAL/AudioEngine.h"
#include "Dependences/Include/al/al.h"
#include "Dependences/Include/al/alc.h"
#include "Dependences/Include/sndfile/sndfile.h"

namespace chaos::audio::openal {


    AudioPlayer::AudioPlayer()
    {

    }


    inline bool AudioPlayer::_makeCurrent()
    {
        if (!this->_context) return false;
        alcMakeContextCurrent(this->_context);

        return true;
    }


    bool AudioPlayer::_initialize()
    {
        if (this->_context) return false;

        if (!this->_audioEngine) return false;
        if (!this->_audioEngine->_device) return false;
        this->_context = alcCreateContext(this->_audioEngine->_device, nullptr);
        if (!this->_context) return false;

        return true;
    }


    bool AudioPlayer::_release()
    {
        if (!this->_makeCurrent()) return false;

        // release buffers
        for (auto& _buffer : this->buffers) {
            alDeleteBuffers(1, &_buffer->_bufferID);
            delete _buffer;
        }
        this->buffers.clear();

        // release sources
        for (auto& _source : this->sources) {
            alDeleteSources(1, &_source->_sourceID);
            delete _source;
        }
        this->sources.clear();

        // release devices
        if (this->_context) alcDestroyContext(this->_context);
        else return false;

        alcMakeContextCurrent(nullptr);
        return true;
    }


    IBuffer* AudioPlayer::loadAudioFile(std::string filename, std::string bufferName)
    {
        if (!this->_makeCurrent()) return nullptr;

        // get information of audio file
        SF_INFO info;
        SNDFILE* file = sf_open(filename.c_str(), SFM_READ, &info);
        if (!file) return nullptr;  // failed to open the file

        // read data from file
        sf_count_t size = info.frames * info.channels;
        std::vector<short> buf(size);
        sf_read_short(file, buf.data(), size);
        // sf_read_int(file, buf.data(), size);
        sf_close(file);

        // infer the format
        ALenum format = (info.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

        size_t in_size = this->buffers.size() + 1;

        // set default name if target name is empty
        if (bufferName == "") bufferName = "Buffer " + std::to_string(in_size);
        else for (auto& buffer : this->buffers) {
            if (buffer->name == bufferName) return nullptr; // the buffer with this name has already existed
        }

        // allocate memory
        this->buffers.resize(in_size, new Buffer());
        auto& _new_buffer = this->buffers.back();

        // generate and initialize buffer
        alGenBuffers(1, &_new_buffer->_bufferID);
        // alBufferi(_new_buffer->_bufferID, AL_FREQUENCY, info.samplerate);
        alBufferData(_new_buffer->_bufferID, format, buf.data(), static_cast<ALsizei>(size * sizeof(short)), info.samplerate);
        alBufferf(_new_buffer->_bufferID, AL_GAIN, 0.1);
        _new_buffer->_audioPlayer = this;
        _new_buffer->name = bufferName;

        return _new_buffer;
    }


    ISource* AudioPlayer::createSource(std::string sourceName)
    {
        if (!this->_makeCurrent()) return nullptr;

        size_t in_size = this->sources.size() + 1;

        // set default name if target name is empty
        if (sourceName == "") sourceName = "Source " + std::to_string(in_size);
        else for (auto& source : this->sources) {
            if (source->name == sourceName) return nullptr; // the source with this name has already existed.
        }

        // allocate memory
        this->sources.resize(in_size, new Source());
        auto& _new_source = this->sources.back();

        // generate and initialize source
        alGenSources(1, &_new_source->_sourceID);
        _new_source->_audioPlayer = this;
        _new_source->name = sourceName;

        _new_source->setVolume(0.5);

        return _new_source;
    }


    bool AudioPlayer::playSource(ISource* source)
    {
        if (!source) return false;  // the source is nullptr

        if (source->_audioPlayer != this) return false; // the source does NOT belong to this audio player

        return source->play();
    }


    bool AudioPlayer::playSource(std::string sourceName)
    {
        if (sourceName.empty()) return false;

        for (auto& source : this->sources)
            if (source->name == sourceName) return source->play();
        return false;   // could NOT find source with this name
    }


}