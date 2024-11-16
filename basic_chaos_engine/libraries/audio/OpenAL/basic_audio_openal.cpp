#pragma once

#include "basic_audio_openal.h"

namespace basic_chaos_engine
{
    basic_audio_openal::basic_audio_openal()
    {
        _device = nullptr;
        _context = nullptr;
    }
    inline int basic_audio_openal::get_error()
    {
        return (_last_error != AL_NO_ERROR) ? _last_error : alGetError();
    }
    bool basic_audio_openal::initialize()
    {
        // create device
        _device = alcOpenDevice(0);
        if (!_device) return false;
        // create context
        _context = alcCreateContext(_device, 0);
        if (!_context)
        {
            alcCloseDevice(_device);
            return false;
        }
        alcMakeContextCurrent(_context);
        return true;
    }
    bool basic_audio_openal::release()
    {
        for (auto& _source_id : vec_source_id) alDeleteSources(1, &_source_id);
        for (auto& _buffer_id : vec_buffer_id) alDeleteBuffers(1, &_buffer_id);
        alcDestroyContext(_context);
        return alcCloseDevice(_device);
    }
    type::BufferID basic_audio_openal::load_sound_file(const std::wstring& filename)
    {
        SF_INFO info{};
        SNDFILE* file = sf_wchar_open(program::locate(filename).c_str(), SFM_READ, &info);
        if (file == nullptr) return 0; // failed to open file
        // read data from file
        sf_count_t items = info.frames * info.channels;
        type::SoundData buf(items);
        sf_read_short(file, buf.data(), items);
        sf_close(file);
        // generate buffer
        ALenum format{};
        format = info.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
        type::BufferID bufferID{};
        alGenBuffers(1, &bufferID);
        alBufferData(bufferID, format, buf.data(), static_cast<ALsizei>(items * sizeof(short)), info.samplerate);
        vec_buffer_id.push_back(bufferID);
        return bufferID;
    }
    type::SourceID basic_audio_openal::create_source()
    {
        type::SourceID sourceID{};
        alGenSources(1, &sourceID);
        vec_source_id.push_back(sourceID);
        return sourceID;
    }
    inline bool basic_audio_openal::source_queue_buffer(type::SourceID source_id, type::BufferID buffer_id)
    {
        alSourceQueueBuffers(source_id, 1, &buffer_id);
        if ((_last_error = alGetError()) != AL_NO_ERROR) return false;
        return true;
    }
    inline bool basic_audio_openal::source_unqueue_buffer(type::SourceID source_id, type::BufferID buffer_id)
    {
        alSourceUnqueueBuffers(source_id, 1, &buffer_id);
        if ((_last_error = alGetError()) != AL_NO_ERROR) return false;
        return true;
    }
    inline bool basic_audio_openal::source_play(type::SourceID source_id)
    {
        alSourcePlay(source_id);
        if ((_last_error = alGetError()) != AL_NO_ERROR) return false;
        return true;
    }
    inline bool basic_audio_openal::source_pause(type::SourceID source_id)
    {
        alSourcePause(source_id);
        if ((_last_error = alGetError()) != AL_NO_ERROR) return false;
        return true;
    }
    inline bool basic_audio_openal::source_stop(type::SourceID source_id)
    {
        alSourceStop(source_id);
        if ((_last_error = alGetError()) != AL_NO_ERROR) return false;
        return true;
    }
    inline bool basic_audio_openal::set_general_speed(ALfloat speed)
    {
        alSpeedOfSound(speed);
        if ((_last_error = alGetError()) != AL_NO_ERROR) return false;
        return true;
    }
    inline bool basic_audio_openal::set_general_pitch(ALfloat pitch)
    {
        alDopplerFactor(pitch);
        if (alGetError() != AL_NO_ERROR) return false;
        return true;
    }
    inline bool basic_audio_openal::source_rewind(type::SourceID source_id)
    {
        alSourceRewind(source_id);
        if ((_last_error = alGetError()) != AL_NO_ERROR) return false;
        return true;
    }
    inline int basic_audio_openal::source_get_playback_position(type::SourceID source_id)
    {
        int _pos = 0;
        alGetSourcei(source_id, AL_SAMPLE_OFFSET, &_pos);
        if ((_last_error = alGetError()) != AL_NO_ERROR) return 0;
        return _pos;
    }
    inline int basic_audio_openal::source_get_playback_time(type::SourceID source_id)
    {
        float _time = 0;
        alGetSourcef(source_id, AL_SEC_OFFSET, &_time);
        if ((_last_error = alGetError()) != AL_NO_ERROR) return 0;
        return static_cast<int>(_time * 1000.f);
    }
    inline bool basic_audio_openal::source_set_playback_position(type::SourceID source_id, int position)
    {
        alSourcei(source_id, AL_SAMPLE_OFFSET, position);
        if ((_last_error = alGetError()) != AL_NO_ERROR) return 0;
        return true;
    }
    inline bool basic_audio_openal::source_set_playback_time(type::SourceID source_id, int time)
    {
        alSourcef(source_id, AL_SEC_OFFSET, static_cast<float>(time) / 1000.f);
        if ((_last_error = alGetError()) != AL_NO_ERROR) return 0;
        return true;
    }
    type::SoundData basic_audio_openal::source_get_sound_data(type::SourceID source_id, int position, int size)
    {
        ALint sample_offset = this->source_get_playback_position(source_id);
        // type::SoundData data(size*);
        return {};
    }
    void basic_audio_openal::buffer_get_sound_data(type::BufferID buffer_id, int position, int size)
    {

    }
}