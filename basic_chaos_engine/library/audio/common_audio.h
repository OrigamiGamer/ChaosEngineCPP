#pragma once

#include "basic_common.h"

#ifdef _OPENAL
#pragma comment(lib,"OpenAL32.lib")

#include "core/al.h"
#include "core/alc.h"

namespace basic_chaos_engine {
    namespace type {
#pragma pack(push,1)
        struct WavHeaderInfo {
            uint32_t chunkID;
            uint32_t chunkSize;
            uint32_t format;
            uint32_t subchunk1ID;
            uint32_t subchunk1Size;
            uint16_t audioFormat;
            uint16_t numChannels;
            uint32_t sampleRate;
            uint32_t byteRate;
            uint16_t blockAlign;
            uint16_t bitsPerSample;
            uint32_t subchunk2ID;
            uint32_t subchunk2Size;
        };
#pragma pack(pop)

        typedef ALuint BufferID;
        typedef ALuint SourceID;
    }
}
#endif