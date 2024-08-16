#pragma once

#include "common.h"

namespace ChaosEngine {
    unsigned long long get_system_time() {
        return std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
    }
}