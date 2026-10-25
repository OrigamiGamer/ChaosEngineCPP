#pragma once

#include "Engine\Include\Core\Handle.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace chaos::core {

    template <typename T>
    class HandleMap {
    private:
        struct Slot {
            std::unique_ptr<T> value;

            /**
             * @brief 槽位世代，用于检验`get()`参数句柄的有效性。
             * @note 只在`remove()`时进入下一代。
             */
            std::uint32_t generation = 1;
        };

        std::vector<Slot> _slots;
        std::vector<std::uint32_t> _free;   // 空闲槽位索引，由占用槽位弹出获得。

    public:
        HandleMap() = default;


        /**
         * @brief 为唯一指针创建句柄，转移唯一指针的所有权到句柄表。
         * @param value 指向数据的唯一指针。
         * @return 返回指针的句柄。
         */
        Handle<T> insert(std::unique_ptr<T> value)
        {
            if (_free.empty())
            {
                _slots.emplace_back();
                Slot& slot = _slots.back();
                slot.value = std::move(value);
                std::uint32_t index = _slots.size() - 1;
                return Handle<T>(index, slot.generation);
            }
            else
            {
                std::uint32_t& index = _free.back();
                _free.pop_back();
                Slot& slot = _slots.at(index);
                slot.value = std::move(value);
                return Handle<T>(index, slot.generation);
            }
            return Handle<T>(INVALID_INDEX, 0);
        }


        /**
         * @brief 移除句柄并释放指针。
         */
        bool remove(Handle<T> handle)
        {
            if (handle.isValid() && handle.index < _slots.size())
            {
                Slot& slot = _slots.at(handle.index);
                std::unique_ptr<T>& value = slot.value;
                value.reset();
                slot.generation++;
                _free.push_back(handle.index);
                return true;
            }
            return false;
        }


        /**
         * @brief 获取句柄对应的指针。
         * @return 返回指向数据的原始指针。
         */
        T* get(Handle<T> handle)
        {
            if (handle.isValid() && handle.index < _slots.size())
            {
                Slot& slot = _slots.at(handle.index);
                std::unique_ptr<T>& value = slot.value;
                return value.get();
            }
            return nullptr;
        }

    };

}