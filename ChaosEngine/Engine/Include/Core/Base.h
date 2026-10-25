#pragma once

#include "Engine/Include/Core/String.h"

namespace chaos::core {

    class Base {
    public:
        core::String name = "Unknown";    // 对象名称

        Base();

        void setName(core::String name);

    };

}