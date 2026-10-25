#pragma once

#include <cstdint>

namespace chaos::core {
    template <typename T>
    class HandleMap;
}

namespace chaos::core {

    inline constexpr std::uint32_t INVALID_INDEX = 0xFFFFFFFFu;

    template <typename T>
    struct Handle {
    public:
        std::uint32_t index = INVALID_INDEX;
        std::uint32_t generation = 0;

    public:
        Handle(std::uint32_t index = INVALID_INDEX, std::uint32_t generation = 0) :
            index(index),
            generation(generation)
        {

        }

    private:
        bool isValid() const
        {
            return index != core::INVALID_INDEX && generation != 0;
        }

        friend class HandleMap<T>;
    };

}