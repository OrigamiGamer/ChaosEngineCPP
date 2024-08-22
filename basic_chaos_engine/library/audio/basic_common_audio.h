#pragma once

#include "basic_common.h"

// libsndfile, a C library for reading and writing files containing sampled audio data.
#pragma comment(lib,"libsndfile.lib")

#include "libsndfile/sndfile.h"

// OpenAL
#ifdef _OPENAL
#pragma comment(lib,"OpenAL32.lib")

#include "OpenAL/core/al.h"
#include "OpenAL/core/alc.h"

namespace basic_chaos_engine {
    namespace type {
        typedef ALuint BufferID;
        typedef ALuint SourceID;
    }
}
#endif

// common_audio
#ifdef _OPENAL
namespace basic_chaos_engine {
    namespace type {
        typedef BufferID HANDLE_SOUND;
    }

    class basic_audio_openal;
}
#endif