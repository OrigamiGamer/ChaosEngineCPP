#pragma once

#include "basic_sound_player.h"

#ifdef _OPENAL
namespace basic_chaos_engine {
    namespace basic_audio {
        basic_sound_player::basic_sound_player() {
        }
        bool basic_sound_player::initialize() {
            if (!openal.initialize()) return false;
            return true;
        }
        bool basic_sound_player::release() {
            if (!openal.release()) return false;
            return true;
        }
        bool basic_sound_player::load_sound_file(const std::wstring& filename, const std::wstring& sound_name) {
            type::HANDLE_SOUND hSound = openal.load_sound_file(filename);
            if (!hSound) return false;  // failed to load sound file
            if (map_sound.find(sound_name) != map_sound.end())
                map_sound.insert({ sound_name, hSound });
            else return false;   // failed to create: sound_name already exists
            return true;
        }
        type::HANDLE_SOUND basic_sound_player::get_sound_handle(const std::wstring& sound_name) {
            if (map_sound.find(sound_name) != map_sound.end())
                return map_sound[sound_name];
            else return 0;  // failed to find sound: sound_name does not exist
        }
        basic_channel basic_sound_player::create_channel(const std::wstring& channel_name) {
            return basic_channel(channel_name);
        }
    }
}
#endif