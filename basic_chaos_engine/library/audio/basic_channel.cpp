#pragma once

#include "basic_channel.h"

namespace basic_chaos_engine {
    namespace basic_audio {
        basic_channel::basic_channel(const std::wstring& channel_name) {
            this->set_name(channel_name);
        }
        void basic_channel::insert_sound(unsigned long long time_point, MAP_SOUND& map_sound) {
            chronoqueue_sound[time_point] = map_sound;
        }
        void basic_channel::insert_sound(unsigned long long time_point, const std::wstring& sound_name, type::HANDLE_SOUND sound_handle) {
            chronoqueue_sound[time_point][sound_name] = sound_handle;
        }
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
        MAP_SOUND basic_channel::get_sound_map(unsigned long long time_point) {
            return chronoqueue_sound[time_point];
        }
        type::HANDLE_SOUND basic_channel::get_sound_handle(unsigned long long time_point, const std::wstring& sound_name) {
            if (chronoqueue_sound.find(time_point) != chronoqueue_sound.end())
                if (chronoqueue_sound.at(time_point).find(sound_name) != chronoqueue_sound.at(time_point).end())
                    return chronoqueue_sound[time_point][sound_name];
            return 0;   // failed to find sound: sound_name does not exist
        }
        inline bool basic_channel::set_name(const std::wstring& name) {
            if (name.empty()) return false;
            channel_name = name;
            return true;
        }
        inline std::wstring basic_channel::get_name() const {
            return channel_name;
        }
    }
}