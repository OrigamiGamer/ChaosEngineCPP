#pragma once

#include "basic_common_audio.h"

namespace basic_chaos_engine {
    namespace basic_audio {
        struct basic_sound {
            std::wstring name;
            type::HANDLE_SOUND handle = 0;
        };
        typedef std::map<const std::wstring, basic_sound> MAP_SOUND;

        struct basic_channel_slice {
            unsigned long long start_time = 0;
            MAP_SOUND map_sound;
        };
        typedef std::vector<basic_channel_slice> CHRONO_QUEUE_SOUND;

        class basic_channel;
        class basic_sound_player;
    }
}

#include "basic_channel.h"
#include "basic_sound_player.h"