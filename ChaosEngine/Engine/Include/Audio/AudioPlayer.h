#pragma once

#include "Engine/Include/Core/String.h"
#include "Engine/Include/Core/Base.h"

namespace chaos::audio {
    class Buffer;
    class Source;
}

namespace chaos::audio {

    class AudioPlayer : public core::Base {
    public:

        AudioPlayer();

        ~AudioPlayer() = default;

        /**
         * @brief 加载音频文件到内存，返回对应音频数据的缓冲区。
         * @param filename 指向音频文件的路径。
         * @param bufferName 缓冲区名称。（可选）
         */
        Buffer* loadAudioFile(core::String filename, core::String bufferName = "");

        /**
         * @brief 创建声源。
         */
        Source* createSource(core::String in_sourceName = "");

        bool playSource(Source* source);
        bool playSource(core::String sourceName);

    };

}