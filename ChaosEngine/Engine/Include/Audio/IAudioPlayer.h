#pragma once

#include "Engine/Include/Core/String.h"
#include "Engine/Include/Core/Base.h"

namespace chaos::audio {
    class IBuffer;
    class ISource;
}

namespace chaos::audio {

    class IAudioPlayer : public core::Base {
    public:

        virtual ~IAudioPlayer() = default;

        /**
         * @brief 加载音频文件到内存，返回对应音频数据的缓冲区。
         * @param filename 指向音频文件的路径。
         * @param bufferName 缓冲区名称。（可选）
         */
        virtual IBuffer* loadAudioFile(core::String filename, core::String bufferName = "") = 0;

        /**
         * @brief 创建声源。
         */
        virtual ISource* createSource(core::String in_sourceName = "") = 0;

        virtual bool playSource(ISource* source) = 0;
        virtual bool playSource(core::String sourceName) = 0;

    };

}