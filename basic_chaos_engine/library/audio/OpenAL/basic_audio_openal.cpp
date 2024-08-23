#pragma once

#include "basic_audio_openal.h"

namespace basic_chaos_engine {
    basic_audio_openal::basic_audio_openal() {
        _device = nullptr;
        _context = nullptr;
    }

    bool basic_audio_openal::initialize() {
        // create device
        _device = alcOpenDevice(NULL);
        if (!_device) return false;
        // create context
        _context = alcCreateContext(_device, NULL);
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
        SNDFILE* file = sf_wchar_open(filename.c_str(), SFM_READ, &info);
        if (!file) return NULL; // failed to open file

        ALenum format{};
        if (info.channels == 1 && info.samplerate == 1)
            format = AL_FORMAT_MONO8;
        else if (info.channels == 1 && info.samplerate == 2)
            format = AL_FORMAT_MONO16;
        else if (info.channels == 2 && info.samplerate == 1)
            format = AL_FORMAT_STEREO8;
        else if (info.channels == 2 && info.samplerate == 2)
            format = AL_FORMAT_STEREO16;
        else return NULL;   // unsupported format

        sf_count_t items = info.frames * info.channels;
        std::vector<short> buf(items);
        sf_read_short(file, buf.data(), items);
        sf_close(file);

        type::BufferID bufferID{};
        alGenBuffers(1, &bufferID);
        alBufferData(bufferID, format, buf.data(), static_cast<ALsizei>(items * sizeof(short)), info.samplerate);
        return bufferID;
    }
}