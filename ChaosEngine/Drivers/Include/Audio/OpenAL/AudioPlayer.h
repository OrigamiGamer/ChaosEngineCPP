#pragma once

#include "Engine/Include/Audio/IAudioPlayer.h"

#include <string>
#include <vector>

class ALCcontext;

namespace chaos::audio::openal {
    class Buffer;
    class Source;
    class AudioEngine;
}

namespace chaos::audio::openal {

    class AudioPlayer final : public chaos::audio::IAudioPlayer {
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
        IBuffer* loadAudioFile(std::string filename, std::string bufferName = "") override;

        ISource* createSource(std::string sourceName = "") override;

        bool playSource(ISource* source) override;
        bool playSource(std::string sourceName) override;

        friend class AudioEngine;
        friend class Buffer;
        friend class Source;
    };

}