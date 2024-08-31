#pragma once

#include "basic_common.h"

// FFTW, a C subroutine library for computing the Discrete Fourier Transform (DFT) in one or more dimensions.
#pragma comment(lib,"fftw3.lib")
#include "fftw3.h"

// libsndfile, a C library for reading and writing files containing sampled audio data.
#pragma comment(lib,"sndfile.lib")
#include "libsndfile/sndfile.h"

// OpenAL, a cross-platform 3D audio API.
#ifdef _OPENAL
#pragma comment(lib,"OpenAL32.lib")
#include "OpenAL/core/al.h"
#include "OpenAL/core/alc.h"

namespace basic_chaos_engine {
    namespace type {
        typedef ALuint BufferID;
        typedef ALuint SourceID;
        typedef std::vector<short> SoundData;
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