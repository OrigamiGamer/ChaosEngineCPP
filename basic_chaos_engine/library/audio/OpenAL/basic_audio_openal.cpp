#pragma once

#include "basic_audio_openal.h"

namespace basic_chaos_engine {
    basic_audio_openal::basic_audio_openal() {
        _device = nullptr;
        _context = nullptr;
    }

    bool basic_audio_openal::initialize() {
        _device = alcOpenDevice(NULL);
        if (!_device) return false;
        _context = alcCreateContext(_device, NULL);
        if (!_context) {
            alcCloseDevice(_device);
            return false;
        }
        alcMakeContextCurrent(_context);
        return true;
    }

    void basic_audio_openal::release() {
        alcDestroyContext(_context);
        alcCloseDevice(_device);
    }

    // File formats support: wav
    type::BufferID basic_audio_openal::load_sound_file(const std::wstring& filename) {
        std::ifstream file(filename, std::ios::binary);
        // WAV
        type::WavHeaderInfo header{};
        file.read(reinterpret_cast<char*>(&header), sizeof(header));
        if (header.chunkID != 0x52494646 || header.format != 0x45564157) {
            file.close();
            return NULL;
        }
        // PCM
        if (header.audioFormat != 1) {
            return NULL;
        }

        std::vector<char> audioData(header.subchunk2Size);
        file.read(audioData.data(), header.subchunk2Size);
        file.close();

        ALenum format{};
        if (header.numChannels == 1 && header.bitsPerSample == 1) {
            format = AL_FORMAT_MONO8;
        }
        else if (header.numChannels == 1 && header.bitsPerSample == 2) {
            format = AL_FORMAT_MONO16;
        }
        else if (header.numChannels == 2 && header.bitsPerSample == 1) {
            format = AL_FORMAT_STEREO8;
        }
        else if (header.numChannels == 2 && header.bitsPerSample == 2) {
            format = AL_FORMAT_STEREO16;
        }
        else return NULL;

        type::BufferID bufferID{};
        alGenBuffers(1, &bufferID);
        alBufferData(bufferID, format, &audioData, header.subchunk2Size, header.sampleRate);
        return bufferID;
    }

    void basic_audio_openal::play() {

    }
}