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
            bool player_playing_state;
            unsigned long long player_time; // Unit: microseconds
            MAP_SOUND map_sound; // single sound resource
            MAP_CHANNEL map_channel;
        public:
            basic_sound_player();
            bool initialize();
            bool release();
            void update(unsigned long long current_time);
            // Load and create a sound from a file. Return false if the file is invalid or the sound name already exists. 
            // The parameter 'soundname' is optional and can be used to get the sound resource later.
            bool load_sound_file(const std::wstring& filename, const std::wstring& sound_name = {});
            // Get a sound resource by name. Return an empty resource if the name is invalid.
            basic_sound get_sound(const std::wstring& sound_name);
            // Get a sound resource by handle. Return an empty resource if the handle is invalid.
            basic_sound get_sound(const type::HANDLE_SOUND& sound_handle);
            // Create a new channel and insert it into the map of channels. Return nullptr if the channel name already exists.
            basic_channel* create_channel(const std::wstring& channel_name);
            // Get a channel by name. Return an empty channel if the name is invalid.
            basic_channel get_channel(const std::wstring& channel_name);
            bool playback();

            // TODO
            bool create_channel_group(const std::wstring& channel_group_name);
        };
    }
}