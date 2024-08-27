#pragma once

#include "basic_common_audio.h"

namespace basic_chaos_engine {
    namespace basic_audio {
        typedef std::map<const std::wstring, type::HANDLE_SOUND> MAP_SOUND;
        typedef std::map<unsigned long long, MAP_SOUND> CHRONO_QUEUE_SOUND;

        class basic_channel;
        class basic_sound_player;
    }
}

#include "basic_channel.h"
#include "basic_sound_player.h"