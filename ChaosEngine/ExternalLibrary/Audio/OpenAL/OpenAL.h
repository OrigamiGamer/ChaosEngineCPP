#pragma once



// STL

#include <vector>
#include <string>



// libsndfile

#include "ExternalLibrary/Audio/libsndfile/sndfile.h"



// openal

#include "ExternalLibrary/Audio/OpenAL/raw/al.h"
#include "ExternalLibrary/Audio/OpenAL/raw/alc.h"



// ----------------
// 1st-declarations
// ----------------

namespace OpenAL {

    class Source;

    class Buffer;

    class AudioEngine;

}



// ----------------
// 2nd-declarations
// ----------------

namespace OpenAL {



    class Source {
    private:
        AudioEngine* _audioEngine = nullptr;
        ALuint _sourceID = 0;

    public:
        std::string name;

        Source();

        friend class AudioEngine;
    };



    class Buffer {
    private:
        AudioEngine* _audioEngine = nullptr;
        ALuint _bufferID = 0;

    public:
        std::string name;

        Buffer();

        friend class AudioEngine;
    };



    class AudioEngine {
    private:
        ALCdevice* _device = nullptr;
        ALCcontext* _context = nullptr;

    public:
        std::vector<Buffer*> buffers;
        std::vector<Source*> sources;

        AudioEngine();

        int getLastError();

        bool initialize();

        bool release();

        Source* createSource(std::string new_sourceName = "");

        // @param filename The absolute path to an audio file.
        Buffer* loadAudioFile(std::string filename, std::string new_bufferName = "");

        friend class Buffer;
        friend class Source;
    };



}
