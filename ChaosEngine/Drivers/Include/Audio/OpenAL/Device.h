#pragma once

#include "Dependences/Include/al/alc.h"

#include <vector>

namespace chaos::audio::openal {
    class Context;
}

namespace chaos::audio::openal {

    /**
     * OpenAL 设备（`ALCdevice` 封装）。
     * 也是 `Context` 的工厂：`createContext()` 创建的上下文由本类持有并统一释放。
     * 资源由析构函数释放，不可拷贝，可通过移动转移所有权。
     * 销毁顺序：`Source/Buffer` -> `Context` -> `Device`。
     */
    class Device {
    private:
        ALCdevice* _device = nullptr;            // 底层设备句柄
        std::vector<Context*> _contexts;         // 工厂持有的上下文

    public:
        /**
         * @brief 构造空设备，不打开任何设备。
         */
        Device();

        /**
         * @brief 析构时自动关闭设备。
         */
        ~Device();

        /**
         * @brief 拷贝构造已删除，禁止拷贝。
         */
        Device(const Device&) = delete;

        /**
         * @brief 拷贝赋值已删除，禁止拷贝。
         */
        Device& operator=(const Device&) = delete;

        /**
         * @brief 移动构造，接管句柄与已创建的上下文，源对象归为空状态。
         */
        Device(Device&& other) noexcept;

        /**
         * @brief 移动赋值，先释放自身资源再接管，源对象归为空状态。
         */
        Device& operator=(Device&& other) noexcept;

        /**
         * @brief 打开音频输出设备。
         * @param deviceName 设备名，`nullptr` 表示默认设备。
         * @return 打开成功返回 `true`。
         */
        bool open(const char* deviceName = nullptr);

        /**
         * @brief 关闭设备，先级联释放本设备创建的所有上下文。幂等，重复调用安全。
         * @return 关闭成功返回 `true`。
         */
        bool close();

        /**
         * @brief 查询设备是否处于打开状态。
         * @return 设备已打开返回 `true`。
         */
        bool isOpen() const;

        /**
         * @brief 工厂：创建上下文。
         * @param attributes 上下文属性列表，`nullptr` 表示默认。
         * @return 上下文指针（由本设备持有），设备未打开或创建失败返回 `nullptr`。
         */
        Context* createContext(const ALCint* attributes = nullptr);

        /**
         * @brief 获取底层 `ALCdevice` 句柄。
         * @return 设备句柄，未打开时为 `nullptr`。
         */
        ALCdevice* handle() const;
    };

}
