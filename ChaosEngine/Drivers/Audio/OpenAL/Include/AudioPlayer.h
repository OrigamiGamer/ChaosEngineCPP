#pragma once

#include "Dependences/Include/al/alc.h"

#include <string>
#include <vector>

namespace chaos::drivers::audio::openal {
    class Buffer;
    class Source;
    class AudioEngine;
}

namespace chaos::drivers::audio::openal {

    class AudioPlayer {
    private:
        AudioEngine* _audioEngine = nullptr;
        ALCcontext* _context = nullptr;

        inline bool _makeCurrent();

        bool _initialize();

        bool _release();

    public:
        std::string name;
        std::vector<Buffer*> buffers;
        std::vector<Source*> sources;

        AudioPlayer();

        // @param filename The absolute path to an audio file.
        Buffer* loadAudioFile(std::string filename, std::string in_bufferName = "");

        Source* createSource(std::string in_sourceName = "");

        bool playSource(Source* source);
        bool playSource(std::string sourceName);

        friend class AudioEngine;
        friend class Buffer;
        friend class Source;
    };

}