#pragma once

#include "basic_audio.h"

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
            std::map<const std::wstring, type::HANDLE_SOUND> map_sound; // single sound resource
        public:
            basic_sound_player();
            bool initialize();
            bool release();
            // Load and create a sound from a file. 'soundname' is optional and can be used to get the sound resource later.
            bool load_sound_file(const std::wstring& filename, const std::wstring& sound_name = {});
            type::HANDLE_SOUND get_sound_handle(const std::wstring& sound_name);
            basic_channel create_channel(const std::wstring& channel_name);
            bool playback();

            // TODO
            bool create_channel_group(const std::wstring& channel_group_name);
        };
    }
}