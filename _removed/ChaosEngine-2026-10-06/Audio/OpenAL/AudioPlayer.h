#pragma once

#include "Engine/Include/Audio/IAudioPlayer.h"

#include "Engine/Include/Core/String.h"

#include <vector>

class ALCcontext;

namespace chaos::audio::openal {
    class Buffer;
    class Source;
    class Device;
}

namespace chaos::audio::openal {

    class AudioPlayer final : public audio::AudioPlayer {
    private:
        Device* _audioEngine = nullptr;
        ALCcontext* _context = nullptr;

        inline bool _makeCurrent();

        bool _initialize();

        bool _release();

    public:
        std::vector<Buffer*> buffers;
        std::vector<Source*> sources;

        AudioPlayer();

        /**
         * @brief 加载音频文件到内存，返回对应音频数据的缓冲区。
         * @param filename 指向音频文件的路径。
         * @param bufferName 缓冲区名称。（可选）
         */
        IBuffer* loadAudioFile(core::String filename, core::String bufferName = "");

        ISource* createSource(core::String sourceName = "");

        bool playSource(ISource* source);
        bool playSource(core::String sourceName);

        friend class Device;
        friend class Buffer;
        friend class Source;
    };

}