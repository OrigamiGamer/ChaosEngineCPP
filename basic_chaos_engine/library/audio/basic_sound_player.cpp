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
        bool basic_sound_player::load_sound_file(const std::wstring& filename, const std::wstring& soundname) {
            type::HANDLE_SOUND hSound = openal.load_sound_file(filename);
            if (!hSound) return false;  // failed to load sound file
            if (map_sound.find(soundname) != map_sound.end())
                map_sound.insert({ soundname, hSound });
            else return false;   // failed to create: soundname already exists
            return true;
        }

    }
}
#endif