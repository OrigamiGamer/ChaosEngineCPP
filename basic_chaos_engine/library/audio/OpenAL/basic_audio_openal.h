#pragma once

#include "common_audio.h"

namespace basic_chaos_engine {
    class basic_audio_openal {
    public:
        ALCdevice* _device;
        ALCcontext* _context;

        basic_audio_openal();
        bool Initialize();
        void Release();
        type::BufferID load_sound_file(const std::wstring& filename);
        void Play();
    };
}