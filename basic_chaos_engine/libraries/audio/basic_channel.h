#pragma once

#include "basic_audio.h"

namespace basic_chaos_engine {
    namespace basic_audio {
        class basic_channel {
        private:
            std::wstring channel_name;
            bool playing_state;
            CHRONO_QUEUE_SOUND chronoqueue_sound;
        public:
            basic_channel();
            basic_channel(const std::wstring& channel_name);

            void update(unsigned long long delta_time);

            // Insert a sound into the map at a time point. Overwrite the existing sound with the same sound name in the map at this time point.
            inline bool insert_sound(unsigned long long time_point, basic_sound sound);
            inline bool insert_sound(unsigned long long time_point, const std::wstring& sound_name, type::HANDLE_SOUND sound_handle);

            // Remove all sounds at a time point.
            inline bool remove(unsigned long long time_point);
            // Remove a sound from a sound name at a time point.
            inline bool remove(unsigned long long time_point, const std::wstring& sound_name);
            // Remove all sounds with a same sound handle at a time point.
            bool remove(unsigned long long time_point, type::HANDLE_SOUND sound_handle);

            // Clear all sounds.
            bool clear();
            // Get the map of sounds at a time point.
            inline MAP_SOUND get_sound_map(unsigned long long time_point);
            // Get the sound handle with a sound name at a time point.
            type::HANDLE_SOUND get_sound_handle(unsigned long long time_point, const std::wstring& sound_name);
            // Set the channel name.
            inline bool set_name(const std::wstring& name);
            // Get the channel name.
            inline std::wstring get_name() const;
        };
    }
}