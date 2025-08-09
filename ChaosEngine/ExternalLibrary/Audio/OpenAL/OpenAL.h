#pragma once

#include <vector>
#include <string>

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
        std::string name = "Source";

        Source();

        friend class AudioEngine;
    };



    class Buffer {
    private:
        AudioEngine* _audioEngine = nullptr;

    public:
        std::string name = "Buffer";

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

        friend class Buffer;
        friend class Source;
    };



}
