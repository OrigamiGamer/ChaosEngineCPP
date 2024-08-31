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
        void basic_sound_player::update(unsigned long long delta_time) {
            player_time += delta_time;


            // if (player_playing_state) {
            //     // foreach channel in map_channel
            //     for (auto& it = map_channel.begin(); it != map_channel.end(); it++) {
            //         auto& _queue_sound = it->second.chronoqueue_sound;
            //         if (it->second.playing_state == false) {
            //             // foreach sound in queue_sound
            //             for (auto& _it = _queue_sound.begin(); _it != _queue_sound.end(); _it++) {
            //                 if (player_time >= _it->start_time) {
            //                     auto& _map_sound = _it->map_sound;
            //                     // foreach sound in map_sound
            //                     for (auto& __it = _map_sound.begin(); __it != _map_sound.end(); __it++) {

            //                     }
            //                     openal.source_play(it->second._source_id);
            //                 }
            //             }
            //         }
            //     }
            // }
        }
        bool basic_sound_player::load_sound_file(const std::wstring& filename, const std::wstring& sound_name) {
            type::HANDLE_SOUND hSound = openal.load_sound_file(filename);
            if (!hSound) return false;  // failed to load sound file
            if (map_sound.find(sound_name) != map_sound.end() || map_sound.empty())
                map_sound[sound_name] = { sound_name, hSound };
            else return false;   // failed to create: sound_name already exists
            return true;
        }

        basic_sound basic_sound_player::get_sound(const std::wstring& sound_name) {
            if (map_sound.find(sound_name) != map_sound.end())
                return map_sound.at(sound_name);
            return {};  // failed to find sound: sound_name does not exist
        }
        basic_sound basic_sound_player::get_sound(const type::HANDLE_SOUND& sound_handle) {
            // foreach sound in map_sound
            for (auto it = map_sound.begin(); it != map_sound.end(); it++)
                if (it->second.handle != sound_handle) return it->second;
            return {};  // failed to find sound: sound_handle does not exist
        }

        basic_channel* basic_sound_player::create_channel(const std::wstring& channel_name) {
            if (map_channel.find(channel_name) != map_channel.end())
                return nullptr;   // failed to insert: channel_name already exists
            map_channel[channel_name] = basic_channel(channel_name);
            auto& _channel = map_channel.at(channel_name);
            _channel.al_source_id = openal.create_source();   // openal::source -> basic_channel
            return &_channel;
        }
        basic_channel basic_sound_player::get_channel(const std::wstring& channel_name) {
            if (map_channel.find(channel_name) != map_channel.end()) return map_channel.at(channel_name);
            return {}; // failed to find channel: channel_name does not exist
        }
        bool basic_sound_player::playback() {
            return false;
        }
    }
}
#endif