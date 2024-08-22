#pragma once

#include "basic_common_audio.h"

namespace basic_chaos_engine {
    class basic_audio_openal {
    public:
        ALCdevice* _device;
        ALCcontext* _context;

        basic_audio_openal();
        bool initialize();
        bool release();
        // Load a sound file from filename, return buffer ID, or NULL if failed.
        // Supported most common formats: WAV, OGG, MP3, FLAC.
        type::BufferID load_sound_file(const std::wstring& filename);
    };
}
