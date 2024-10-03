#pragma once

#include "common.h"

namespace ChaosEngine {
    inline unsigned long long get_system_time() {
        return std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
        ).count();
    }
}

#include "Common_PhysicsEngine.cpp"