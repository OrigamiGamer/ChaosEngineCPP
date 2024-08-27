#pragma once

#include "basic_sound_player.h"

#ifdef _OPENAL
namespace basic_chaos_engine {
    namespace basic_audio {
        // basic_channel

        void basic_channel::insert_sound(unsigned long long time_point, MAP_SOUND& map_sound) {
            chronoqueue_sound[time_point] = map_sound;
        }
        void basic_channel::insert_sound(unsigned long long time_point, const std::wstring& sound_name, type::HANDLE_SOUND sound_handle) {}

        bool basic_channel::remove(unsigned long long time_point) {
            return chronoqueue_sound.erase(time_point) > 0;
        }
        bool basic_channel::remove(unsigned long long time_point, const std::wstring& sound_name) {
            if (chronoqueue_sound.find(time_point) != chronoqueue_sound.end())
                return chronoqueue_sound.at(time_point).erase(sound_name) > 0;
            return false;
        }
        bool basic_channel::remove(unsigned long long time_point, type::HANDLE_SOUND sound_handle) {
            if (chronoqueue_sound.find(time_point) != chronoqueue_sound.end()) {
                auto _node_map_sound = chronoqueue_sound.at(time_point);
                // foreach sound in map_sound at time_point
                for (auto it = _node_map_sound.begin(); it != _node_map_sound.end(); it++)
                    if (it->second == sound_handle) return _node_map_sound.erase(it->first) > 0;
            }
            return false;
        }

        bool basic_channel::clear() {
            if (chronoqueue_sound.empty()) return false;
            chronoqueue_sound.clear();
            return true;
        }

        bool basic_channel::set_name(const std::wstring& name) {
            if (name.empty()) return false;
            channel_name = name;
            return true;
        }


        // basic_sound_player

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
        type::HANDLE_SOUND basic_sound_player::get_sound_handle(const std::wstring& soundname) {
            if (map_sound.find(soundname) != map_sound.end())
                return map_sound[soundname];
            else return 0;  // failed to find sound: soundname does not exist
        }
        basic_channel basic_sound_player::create_channel(const std::wstring& channel_name) {

        }
    }
}
#endif