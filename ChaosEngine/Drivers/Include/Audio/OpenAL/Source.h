#pragma once

#include "Dependences/Include/al/al.h"

namespace chaos::audio::openal {
    class Context;
    class Buffer;
}

namespace chaos::audio::openal {

    /**
     * 播放源（`ALuint` 源对象封装）。
     * 由 `Context` 工厂创建并持有，调用方不负责释放。
     * 每个方法调用前先将所属上下文设为当前上下文。
     * 所属上下文必须比本对象长寿。
     * 资源由析构函数释放，不可拷贝。
     * 销毁顺序：`Source/Buffer` -> `Context` -> `Device`。
     */
    class Source {
    private:
        Context* _context = nullptr;    // 所属上下文
        ALuint _source = 0;             // 底层源对象句柄

        /**
         * @brief 构造空源对象，由工厂调用。
         */
        Source();

        /**
         * @brief 析构时自动删除源对象。
         */
        ~Source();

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
        Source(const Source&) = delete;

        /**
         * @brief 拷贝赋值已删除，禁止拷贝。
         */
        Source& operator=(const Source&) = delete;

        /**
         * @brief 删除源对象。幂等，重复调用安全。
         * @return 删除成功返回 `true`。
         */
        bool destroy();

        /**
         * @brief 查询源对象是否有效。
         * @return 源已生成返回 `true`。
         */
        bool isValid() const;

        /**
         * @brief 播放、重播或恢复本源。
         * @return 调用成功返回 `true`。
         */
        bool play();

        /**
         * @brief 暂停本源。
         * @return 调用成功返回 `true`。
         */
        bool pause();

        /**
         * @brief 停止本源。
         * @return 调用成功返回 `true`。
         */
        bool stop();

        /**
         * @brief 停止本源并复位到初始状态。
         * @return 调用成功返回 `true`。
         */
        bool rewind();

        /**
         * @brief 获取播放状态。
         * @return `AL_INITIAL` / `AL_PLAYING` / `AL_PAUSED` / `AL_STOPPED` 之一，失败返回 `0`。
         */
        ALenum state() const;

        /**
         * @brief 将缓冲区排入队列。
         * @param bufferIds 缓冲区句柄数组。
         * @param count 数组元素个数。
         * @return 调用成功返回 `true`。
         */
        bool queueBuffers(const ALuint* bufferIds, ALsizei count);

        /**
         * @brief 从队列中移除已处理的缓冲区。
         * @param bufferIds 缓冲区句柄数组。
         * @param count 数组元素个数。
         * @return 调用成功返回 `true`。
         */
        bool unqueueBuffers(ALuint* bufferIds, ALsizei count);

        /**
         * @brief 获取队列中的缓冲区数量。
         * @return 缓冲区数量，失败返回 `0`。
         */
        ALint queuedBufferCount() const;

        /**
         * @brief 获取已处理、可回收的缓冲区数量。
         * @return 缓冲区数量，失败返回 `0`。
         */
        ALint processedBufferCount() const;

        /**
         * @brief 绑定单个静态缓冲区。
         * @param buffer 已创建的缓冲区。
         * @return 绑定成功返回 `true`。
         */
        bool setBuffer(const Buffer& buffer);

        /**
         * @brief 解除静态缓冲区绑定。
         * @return 调用成功返回 `true`。
         */
        bool detachBuffer();

        /**
         * @brief 设置增益。
         * @param gain 增益值（`0.0` ~ `1.0`）。
         * @return 设置成功返回 `true`。
         */
        bool setGain(ALfloat gain);

        /**
         * @brief 获取增益。
         * @return 增益值，失败返回 `0.0`。
         */
        ALfloat getGain() const;

        /**
         * @brief 设置音调倍率。
         * @param pitch 音调倍率（`1.0` 为原速）。
         * @return 设置成功返回 `true`。
         */
        bool setPitch(ALfloat pitch);

        /**
         * @brief 获取音调倍率。
         * @return 音调倍率，失败返回 `0.0`。
         */
        ALfloat getPitch() const;

        /**
         * @brief 设置是否循环播放。
         * @param looping 是否循环。
         * @return 设置成功返回 `true`。
         */
        bool setLooping(ALboolean looping);

        /**
         * @brief 设置时间偏移。
         * @param seconds 时间偏移（单位：秒）。
         * @return 设置成功返回 `true`。
         */
        bool setTimeOffset(ALfloat seconds);

        /**
         * @brief 获取时间偏移。
         * @return 时间偏移（单位：秒），失败返回 `-1.0`。
         */
        ALfloat getTimeOffset() const;

        /**
         * @brief 设置采样偏移。
         * @param samples 采样偏移。
         * @return 设置成功返回 `true`。
         */
        bool setSampleOffset(ALint samples);

        /**
         * @brief 获取采样偏移。
         * @return 采样偏移，失败返回 `-1`。
         */
        ALint getSampleOffset() const;

        /**
         * @brief 设置空间位置。
         * @param x X 坐标。
         * @param y Y 坐标。
         * @param z Z 坐标。
         * @return 设置成功返回 `true`。
         */
        bool setPosition(ALfloat x, ALfloat y, ALfloat z);

        /**
         * @brief 获取底层 `ALuint` 句柄。
         * @return 源对象句柄，未生成时为 `0`。
         */
        ALuint handle() const;
    };

}
