#pragma once

#include "common_audio.h"

namespace basic_chaos_engine {
    namespace basic_audio {

        struct basic_sound;
        struct basic_channel_slice;
        class basic_channel;

        typedef std::map<const std::wstring, basic_sound> MAP_SOUND;    // map of sounds
        typedef std::vector<basic_channel_slice> CHRONO_QUEUE_SOUND;    // chrono-queue of sounds
        typedef std::map<const std::wstring, basic_channel> MAP_CHANNEL;    // map of channels

        struct basic_sound {
            std::wstring name;
            type::HANDLE_SOUND handle = 0;
            basic_sound() {}
            basic_sound(type::HANDLE_SOUND handle) : handle(handle) {}
            basic_sound(const std::wstring& name, type::HANDLE_SOUND handle) : name(name), handle(handle) {}
        };

        struct basic_channel_slice {
            unsigned long long start_time = 0;
            MAP_SOUND map_sound;
        };

        class basic_sound_player;
    }
}

#include "basic_channel.h"
#include "basic_sound_player.h"