#pragma once

#include <string>

namespace chaos::audio {
    class IBuffer;
    class ISource;
}

namespace chaos::audio {

    class IAudioPlayer {
    public:

        virtual ~IAudioPlayer() = default;

        /**
         * @brief 加载音频文件到内存，返回对应音频数据的缓冲区。
         * @param filename 指向音频文件的路径。
         * @param bufferName 缓冲区名称。（可选）
         */
        virtual IBuffer* loadAudioFile(std::string filename, std::string bufferName = "") = 0;

        virtual ISource* createSource(std::string in_sourceName = "") = 0;

        virtual bool playSource(ISource* source) = 0;
        virtual bool playSource(std::string sourceName) = 0;

    };

}