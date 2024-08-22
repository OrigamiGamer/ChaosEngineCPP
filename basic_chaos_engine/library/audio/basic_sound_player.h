#pragma once

#include "basic_common_audio.h"

#ifdef _OPENAL
#include "OpenAL/basic_audio_openal.h"
#endif

namespace basic_chaos_engine {
    namespace basic_audio {
        class basic_sound_player {
        private:
#ifdef _OPENAL
            basic_audio_openal openal;
#endif
        public:
            std::vector<type::HANDLE_SOUND> vec_sound;
        public:
            basic_sound_player();
            bool initialize();
            bool release();
            bool load_sound_file(const std::wstring& filename);
        };
    }
}