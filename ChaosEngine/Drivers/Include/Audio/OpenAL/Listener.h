#pragma once

#include "Dependences/Include/al/al.h"

namespace chaos::audio::openal {
    class Context;
}

namespace chaos::audio::openal {

    /**
     * 听者（`alListener*` 封装）。
     * 由 `Context` 工厂创建并持有，调用方不负责释放。
     * 听者没有独立的 AL 对象，从属于上下文；每个方法调用前先将所属上下文设为当前上下文。
     * 所属上下文必须比本对象长寿。
     */
    class Listener {
    private:
        Context* _context = nullptr;    // 所属上下文

        /**
         * @brief 构造听者并绑定所属上下文，由工厂调用。
         * @param context 听者所属的上下文。
         */
        explicit Listener(Context& context);

        /**
         * @brief 析构不释放任何资源。
         */
        ~Listener() = default;

        friend class Context;

    public:
        /**
         * @brief 拷贝构造已删除，禁止拷贝。
         */
        Listener(const Listener&) = delete;

        /**
         * @brief 拷贝赋值已删除，禁止拷贝。
         */
        Listener& operator=(const Listener&) = delete;

        /**
         * @brief 设置听者增益。
         * @param gain 增益值（`0.0` ~ `1.0`）。
         * @return 设置成功返回 `true`。
         */
        bool setGain(ALfloat gain);

        /**
         * @brief 获取听者增益。
         * @return 增益值，失败返回 `0.0`。
         */
        ALfloat getGain() const;

        /**
         * @brief 设置听者位置。
         * @param x X 坐标。
         * @param y Y 坐标。
         * @param z Z 坐标。
         * @return 设置成功返回 `true`。
         */
        bool setPosition(ALfloat x, ALfloat y, ALfloat z);

        /**
         * @brief 获取听者位置。
         * @param x 输出 X 坐标。
         * @param y 输出 Y 坐标。
         * @param z 输出 Z 坐标。
         * @return 获取成功返回 `true`。
         */
        bool getPosition(ALfloat& x, ALfloat& y, ALfloat& z) const;

        /**
         * @brief 设置听者速度。
         * @param x X 速度分量。
         * @param y Y 速度分量。
         * @param z Z 速度分量。
         * @return 设置成功返回 `true`。
         */
        bool setVelocity(ALfloat x, ALfloat y, ALfloat z);

        /**
         * @brief 获取听者速度。
         * @param x 输出 X 速度分量。
         * @param y 输出 Y 速度分量。
         * @param z 输出 Z 速度分量。
         * @return 获取成功返回 `true`。
         */
        bool getVelocity(ALfloat& x, ALfloat& y, ALfloat& z) const;

        /**
         * @brief 设置听者朝向。
         * @param values 前 3 个为前向向量，后 3 个为向上向量，共 6 个 `float`。
         * @return 设置成功返回 `true`。
         */
        bool setOrientation(const ALfloat values[6]);

        /**
         * @brief 获取听者朝向。
         * @param values 输出数组，前 3 个为前向向量，后 3 个为向上向量，共 6 个 `float`。
         * @return 获取成功返回 `true`。
         */
        bool getOrientation(ALfloat values[6]) const;
    };

}
