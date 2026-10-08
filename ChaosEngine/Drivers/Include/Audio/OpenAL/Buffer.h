#pragma once

#include "Dependences/Include/al/al.h"

namespace chaos::audio::openal {
    class Context;
}

namespace chaos::audio::openal {

    /**
     * 音频缓冲区（`ALuint` 缓冲对象封装）。
     * 由 `Context` 工厂创建并持有，调用方不负责释放。
     * 每个方法调用前先将所属上下文设为当前上下文。
     * 所属上下文必须比本对象长寿。
     * 资源由析构函数释放，不可拷贝。
     * 销毁顺序：`Source/Buffer` -> `Context` -> `Device`。
     */
    class Buffer {
    private:
        Context* _context = nullptr;    // 所属上下文
        ALuint _buffer = 0;             // 底层缓冲区句柄

        /**
         * @brief 构造空缓冲区，由工厂调用。
         */
        Buffer();

        /**
         * @brief 析构时自动删除缓冲区对象。
         */
        ~Buffer();

        /**
         * @brief 将所属上下文设为当前上下文。
         * @return 设置成功返回 `true`。
         */
        bool _makeCurrent() const;

        friend class Context;

    public:
        /**
         * @brief 拷贝构造已删除，禁止拷贝。
         */
        Buffer(const Buffer&) = delete;

        /**
         * @brief 拷贝赋值已删除，禁止拷贝。
         */
        Buffer& operator=(const Buffer&) = delete;

        /**
         * @brief 删除缓冲区对象。幂等，重复调用安全。
         * @return 删除成功返回 `true`。
         */
        bool destroy();

        /**
         * @brief 查询缓冲区对象是否有效。
         * @return 缓冲区已生成返回 `true`。
         */
        bool isValid() const;

        /**
         * @brief 写入音频数据。
         * @param format 音频格式（如 `AL_FORMAT_MONO16`、`AL_FORMAT_STEREO16`）。
         * @param data 音频数据。
         * @param size 数据字节数。
         * @param frequency 采样率。
         * @return 写入成功返回 `true`。
         */
        bool setData(ALenum format, const void* data, ALsizei size, ALsizei frequency);

        /**
         * @brief 读取缓冲区整型属性。
         * @param param 属性名（`AL_FREQUENCY`、`AL_BITS`、`AL_CHANNELS`、`AL_SIZE`）。
         * @return 属性值，失败返回 `0`。
         */
        ALint getInteger(ALenum param) const;

        /**
         * @brief 获取底层 `ALuint` 句柄。
         * @return 缓冲区句柄，未生成时为 `0`。
         */
        ALuint handle() const;
    };

}
