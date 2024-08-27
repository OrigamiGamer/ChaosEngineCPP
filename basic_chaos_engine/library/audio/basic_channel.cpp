#pragma once

#include "basic_channel.h"

namespace basic_chaos_engine {
    namespace basic_audio {
        basic_channel::basic_channel() {
            this->set_name(L"default");
        }
        basic_channel::basic_channel(const std::wstring& channel_name) {
            this->set_name(channel_name);
        }
        inline bool basic_channel::insert_sound(unsigned long long time_point, basic_sound sound) {
            if (sound.name.empty() || sound.handle == 0) return false;
            chronoqueue_sound[time_point][sound.name] = sound.handle;
            return true;
        }
        inline bool basic_channel::insert_sound(unsigned long long time_point, const std::wstring& sound_name, type::HANDLE_SOUND sound_handle) {
            return this->insert_sound(time_point, { sound_name, sound_handle });
        }

        inline bool basic_channel::remove(unsigned long long time_point) {
            // return chronoqueue_sound.erase(time_point) > 0;
        }
        inline bool basic_channel::remove(unsigned long long time_point, const std::wstring& sound_name) {
            // if (chronoqueue_sound.find(time_point) != chronoqueue_sound.end())
            //     return chronoqueue_sound.at(time_point).erase(sound_name) > 0;
            // return false;
        }
        bool basic_channel::remove(unsigned long long time_point, type::HANDLE_SOUND sound_handle) {
            // if (chronoqueue_sound.find(time_point) != chronoqueue_sound.end()) {
            //     auto _node_map_sound = chronoqueue_sound.at(time_point);
            //     // foreach sound in map_sound at time_point
            //     for (auto it = _node_map_sound.begin(); it != _node_map_sound.end(); it++)
            //         if (it->second != sound_handle) return _node_map_sound.erase(it->first) > 0;
            // }
            // return false;
        }

        bool basic_channel::clear() {
            if (chronoqueue_sound.empty()) return false;
            chronoqueue_sound.clear();
            return true;
        }
        inline MAP_SOUND basic_channel::get_sound_map(unsigned long long time_point) {
            // return chronoqueue_sound[time_point];
        }
        type::HANDLE_SOUND basic_channel::get_sound_handle(unsigned long long time_point, const std::wstring& sound_name) {
            // if (chronoqueue_sound.find(time_point) != chronoqueue_sound.end())
            //     if (chronoqueue_sound.at(time_point).find(sound_name) != chronoqueue_sound.at(time_point).end())
            //         return chronoqueue_sound[time_point][sound_name];
            // return 0;   // failed to find sound: sound_name does not exist
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