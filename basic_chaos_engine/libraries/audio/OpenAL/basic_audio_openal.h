#pragma once

#include "common_audio.h"

namespace basic_chaos_engine
{
    class basic_audio_openal
    {
    private:
        ALenum _last_error;
        ALCdevice* _device;
        ALCcontext* _context;
    public:
        std::vector<type::BufferID> vec_buffer_id;
        std::vector<type::SourceID> vec_source_id;

        basic_audio_openal();
        inline ALenum get_error();
        bool initialize();
        bool release();
        // Load a sound file from filename. Return buffer ID, or NULL if failed.
        // Supported most common formats: WAV, OGG, MP3, FLAC.
        type::BufferID load_sound_file(const std::wstring& filename);
        // Create a source. Return source ID, or NULL if failed.
        // The default general speed value is 343.3.
        inline bool set_general_speed(ALfloat speed);
        inline bool set_general_pitch(ALfloat pitch);

        void buffer_get_sound_data(type::BufferID buffer_id, int position, int size);

        type::SourceID create_source();

        // Queue a buffer to a source. Return false if the ID of source or buffer is invalid.
        inline bool source_queue_buffer(type::SourceID source_id, type::BufferID buffer_id);

        // Unqueue a buffer from a source. Return false if the ID of source or buffer is invalid.
        inline bool source_unqueue_buffer(type::SourceID source_id, type::BufferID buffer_id);

        // Playback a source. Return false if the ID of source is invalid.
        inline bool source_play(type::SourceID source_id);
        inline bool source_pause(type::SourceID source_id);
        inline bool source_stop(type::SourceID source_id);
        inline bool source_rewind(type::SourceID source_id);

        inline int source_get_volume(type::SourceID source_id, float volume);

        inline int source_get_playback_position(type::SourceID source_id);

        // Units: milliseconds(ms).
        inline int source_get_playback_time(type::SourceID source_id);

        inline float source_get_volume(type::SourceID source_id);

        inline bool source_set_playback_position(type::SourceID source_id, int position);

        // Units: milliseconds(ms).
        inline bool source_set_playback_time(type::SourceID source_id, int time);

        inline bool source_set_volume(type::SourceID source_id, float volume);

        // TODO: connect TTFW, libsndfile and OpenAL.
        type::SoundData source_get_sound_data(type::SourceID source_id, int position, int size);
    };
}