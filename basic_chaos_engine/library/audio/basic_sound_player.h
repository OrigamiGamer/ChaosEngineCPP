#pragma once

#include "basic_common_audio.h"

#ifdef _OPENAL
#include "OpenAL/basic_audio_openal.h"
#endif

namespace basic_chaos_engine {
    namespace basic_audio {
        typedef std::map<const std::wstring, type::HANDLE_SOUND> MAP_SOUND;
        typedef std::map<unsigned long long, MAP_SOUND> CHRONO_QUEUE_SOUND;

        class basic_channel {
        private:
            std::wstring channel_name;
            CHRONO_QUEUE_SOUND chronoqueue_sound;
        public:
            // Insert a map of sounds at a time point. Overwrite the existing sounds at this time point.
            void insert_sound(unsigned long long time_point, MAP_SOUND& map_sound);
            // TODO: Insert a sound into the map of sounds at a time point. Overwrite the existing sound with the same sound name at this time point.
            void insert_sound(unsigned long long time_point, const std::wstring& sound_name, type::HANDLE_SOUND sound_handle);

            // Remove all sounds at a time point.
            bool remove(unsigned long long time_point);
            // Remove a sound from a sound name at a time point.
            bool remove(unsigned long long time_point, const std::wstring& sound_name);
            // Remove all sounds with a same sound handle at a time point.
            bool remove(unsigned long long time_point, type::HANDLE_SOUND sound_handle);

            // Clear all sounds.
            bool clear();

            // Set the channel name.
            bool set_name(const std::wstring& channel_name);
        };

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
            bool load_sound_file(const std::wstring& filename, const std::wstring& soundname = {});
            type::HANDLE_SOUND get_sound_handle(const std::wstring& soundname);
            basic_channel create_channel(const std::wstring& channel_name);
            bool create_channel_group(const std::wstring& channel_group_name);
            bool playback();
        };
    }
}