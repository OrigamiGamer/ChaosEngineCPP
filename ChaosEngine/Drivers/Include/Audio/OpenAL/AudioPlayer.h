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

        /**
         * @brief 加载音频文件到内存，返回对应音频数据的缓冲区。
         * @param filename 指向音频文件的路径。
         * @param bufferName 缓冲区名称。（可选）
         */
        Buffer* loadAudioFile(std::string filename, std::string bufferName = "");

        Source* createSource(std::string in_sourceName = "");

        bool playSource(Source* source);
        bool playSource(std::string sourceName);

        friend class AudioEngine;
        friend class Buffer;
        friend class Source;
    };

}