#pragma once

#include "Dependences/Include/al/alc.h"

#include <vector>

namespace chaos::audio::openal {
    class Device;
    class Buffer;
    class Source;
    class Listener;
}

namespace chaos::audio::openal {

    /**
     * OpenAL 上下文（`ALCcontext` 封装）。
     * 由 `Device` 工厂创建并持有，调用方不负责释放；同时是 `Buffer`/`Source`/`Listener` 的工厂。
     * 资源由析构函数释放，不可拷贝，可通过移动转移所有权。
     * 销毁顺序：`Source/Buffer` -> `Context` -> `Device`。
     */
    class Context {
    private:
        ALCcontext* _context = nullptr;            // 底层上下文句柄
        std::vector<Buffer*> _buffers;             // 工厂持有的缓冲区
        std::vector<Source*> _sources;             // 工厂持有的播放源
        std::vector<Listener*> _listeners;         // 工厂持有的听者

        /**
         * @brief 构造空上下文，由工厂调用。
         */
        Context();

        /**
         * @brief 创建上下文。（由 `Device` 工厂调用）
         * @param device 已打开的设备。
         * @param attributes 上下文属性列表，`nullptr` 表示默认。
         * @return 创建成功返回 `true`。
         */
        bool create(Device& device, const ALCint* attributes);

        friend class Device;

    public:
        /**
         * @brief 析构时自动销毁上下文并级联释放子对象。
         */
        ~Context();

        /**
         * @brief 拷贝构造已删除，禁止拷贝。
         */
        Context(const Context&) = delete;

        /**
         * @brief 拷贝赋值已删除，禁止拷贝。
         */
        Context& operator=(const Context&) = delete;

        /**
         * @brief 移动构造，接管句柄与子对象，源对象归为空状态，子对象反指同步修正。
         */
        Context(Context&& other) noexcept;

        /**
         * @brief 移动赋值，先释放自身资源再接管，源对象归为空状态，子对象反指同步修正。
         */
        Context& operator=(Context&& other) noexcept;

        /**
         * @brief 工厂：创建缓冲区。
         * @return 缓冲区指针（由本上下文持有），上下文无效或创建失败返回 `nullptr`。
         */
        Buffer* createBuffer();

        /**
         * @brief 工厂：创建播放源。
         * @return 播放源指针（由本上下文持有），上下文无效或创建失败返回 `nullptr`。
         */
        Source* createSource();

        /**
         * @brief 工厂：创建听者。
         * @return 听者指针（由本上下文持有），上下文无效或创建失败返回 `nullptr`。
         */
        Listener* createListener();

        /**
         * @brief 销毁上下文，级联释放本上下文创建的所有子对象。幂等，重复调用安全。
         * @return 销毁成功返回 `true`。
         */
        bool destroy();

        /**
         * @brief 查询上下文是否有效。
         * @return 上下文已创建返回 `true`。
         */
        bool isValid() const;

        /**
         * @brief 将本上下文设为当前上下文。
         * @return 设置成功返回 `true`。
         */
        bool makeCurrent();

        /**
         * @brief 取消当前上下文。
         * @return 取消成功返回 `true`。
         */
        static bool makeNoneCurrent();

        /**
         * @brief 挂起本上下文的处理。
         */
        void suspend();

        /**
         * @brief 继续本上下文的处理。
         */
        void process();

        /**
         * @brief 获取底层 `ALCcontext` 句柄。
         * @return 上下文句柄，未创建时为 `nullptr`。
         */
        ALCcontext* handle() const;
    };

}
