#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace Type {
        struct Size {
            float length, width, height;
        };
        struct Size2D {
            float width, height;
            Size2D() = default;
        };
        struct Position {
            float x, y, z;
        };
        struct Position2D {
            float x, y;
        };

    }

}