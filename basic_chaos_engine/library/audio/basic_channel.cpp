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

            basic_channel_slice* _slice_overwrite = nullptr;
            for (auto& _slice : chronoqueue_sound)
                if (_slice.start_time == time_point) _slice_overwrite = &_slice;

            if (_slice_overwrite != nullptr)
                // 'overwrite' an existing map of sounds at the time point
                _slice_overwrite->map_sound.insert_or_assign(sound.name, sound.handle);
            else {
                // 'create' a new map of sounds at the time point
                basic_channel_slice _new_slice;
                _new_slice.map_sound.insert_or_assign(sound.name, sound.handle);
                _new_slice.start_time = time_point;
                chronoqueue_sound.push_back(_new_slice);
            }

            // 'sort' the chronoqueue_sound by time point
            std::sort(chronoqueue_sound.begin(), chronoqueue_sound.end(),
                [](basic_channel_slice& a, basic_channel_slice& b) {
                    return a.start_time < b.start_time;
                }
            );
            return true;
        }
        inline bool basic_channel::insert_sound(unsigned long long time_point, const std::wstring& sound_name, type::HANDLE_SOUND sound_handle) {
            return this->insert_sound(time_point, { sound_name, sound_handle });
        }

        inline bool basic_channel::remove(unsigned long long time_point) {
            for (auto& it = chronoqueue_sound.begin(); it != chronoqueue_sound.end(); it++)
                if (it->start_time == time_point) {
                    chronoqueue_sound.erase(it);
                    return true;
                }
            return false;
        }
        inline bool basic_channel::remove(unsigned long long time_point, const std::wstring& sound_name) {
            for (auto& it = chronoqueue_sound.begin(); it != chronoqueue_sound.end(); it++)
                if (it->start_time == time_point) {
                    auto& _node_map_sound = it->map_sound;
                    if (_node_map_sound.find(sound_name) != _node_map_sound.end()) {
                        _node_map_sound.erase(sound_name);
                        return true;
                    }
                }
            return false;
        }
        bool basic_channel::remove(unsigned long long time_point, type::HANDLE_SOUND sound_handle) {
            for (auto& it = chronoqueue_sound.begin(); it != chronoqueue_sound.end(); it++)
                if (it->start_time == time_point) {
                    auto& _node_map_sound = it->map_sound;
                    for (auto& _it = _node_map_sound.begin(); _it != _node_map_sound.end(); _it++)
                        if (_it->second.handle == sound_handle) {
                            _node_map_sound.erase(_it);
                            return true;
                        }
                }
            return false;
        }

        bool basic_channel::clear() {
            if (chronoqueue_sound.empty()) return false;
            chronoqueue_sound.clear();
            return true;
        }
        inline MAP_SOUND basic_channel::get_sound_map(unsigned long long time_point) {
            for (auto& it = chronoqueue_sound.begin(); it != chronoqueue_sound.end(); it++)
                if (it->start_time == time_point) return it->map_sound;
            return {};   // failed to find time_point: time_point does not exist
        }
        type::HANDLE_SOUND basic_channel::get_sound_handle(unsigned long long time_point, const std::wstring& sound_name) {
            for (auto& it = chronoqueue_sound.begin(); it != chronoqueue_sound.end(); it++)
                if (it->start_time == time_point) {
                    auto& _node_map_sound = it->map_sound;
                    if (_node_map_sound.find(sound_name) != _node_map_sound.end())
                        return _node_map_sound.at(sound_name).handle;
                }
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