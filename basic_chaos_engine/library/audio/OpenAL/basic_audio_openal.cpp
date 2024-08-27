#pragma once

#include "basic_audio_openal.h"

namespace basic_chaos_engine {
    basic_audio_openal::basic_audio_openal() {
        _device = nullptr;
        _context = nullptr;
    }

    bool basic_audio_openal::initialize() {
        // create device
        _device = alcOpenDevice(0);
        if (!_device) return false;
        // create context
        _context = alcCreateContext(_device, 0);
        if (!_context) {
            alcCloseDevice(_device);
            return false;
        }
        alcMakeContextCurrent(_context);
        return true;
    }

    bool basic_audio_openal::release() {
        alcDestroyContext(_context);
        return alcCloseDevice(_device);
    }

    type::BufferID basic_audio_openal::load_sound_file(const std::wstring& filename) {
        SF_INFO info{};
        SNDFILE* file = sf_wchar_open(program::locate(filename).c_str(), SFM_READ, &info);
        if (file == nullptr) return 0; // failed to open file

        ALenum format{};
        format = info.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

        sf_count_t items = info.frames * info.channels;
        std::vector<short> buf(items);
        sf_read_short(file, buf.data(), items);
        sf_close(file);

        type::BufferID bufferID{};
        alGenBuffers(1, &bufferID);
        alBufferData(bufferID, format, buf.data(), static_cast<ALsizei>(items * sizeof(short)), info.samplerate);
        return bufferID;
    }
    type::SourceID basic_audio_openal::create_source() {
        type::SourceID sourceID{};
        alGenSources(1, &sourceID);
        return sourceID;
    }
    bool basic_audio_openal::source_add_buffer(type::SourceID sourceID, type::BufferID bufferID) {
        if (sourceID == 0 || bufferID == 0) return false;
        alSourcei(sourceID, AL_BUFFER, bufferID);
        return true;
    }
    bool basic_audio_openal::source_play(type::SourceID sourceID) {
        if (sourceID == 0) return false;
        alSourcePlay(sourceID);
        return true;
    }
}