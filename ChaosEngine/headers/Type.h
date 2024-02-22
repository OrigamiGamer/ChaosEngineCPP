#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    // Types which engine predefined
    namespace Type {

        // Callback EngineProc
        typedef BOOL(CALLBACK* ENGINEPROC)();

        // Initial Property
        struct WindowInitialProperty {
            int width = CW_USEDEFAULT, height = CW_USEDEFAULT;
            int x = CW_USEDEFAULT, y = CW_USEDEFAULT;
            std::wstring WndTitle = L"New Game";
            HWND hWndParent = NULL;
        };
        struct EngineStartupProperty {
            ENGINEPROC pGameMain = nullptr;
            ENGINEPROC pGameExit = nullptr;
            int FPS = 60;
        };

        // Basic Types
        struct SIZE {
            float width, height;

            SIZE() = default;
            SIZE(float width, float height) : width(width), height(height) {};

            bool operator==(SIZE other) const {
                return width == other.width || height == other.height;
            }
            bool operator!=(SIZE other) const {
                return !(*this == other);
            }
        };
        struct SIZE_3D {
            float width, height, length;

            SIZE_3D() = default;
            SIZE_3D(float width, float height, float length) : width(width), height(height), length(length) {};

            bool operator==(SIZE_3D other) const {
                return width == other.width && height == other.height && length == other.length;
            }
            bool operator!=(SIZE_3D other) const {
                return !(*this == other);
            }
        };

        struct POS {
            float x = 0, y = 0;

            POS() = default;
            POS(float x, float y) : x(x), y(y) {};

            bool operator==(POS other) const {
                return x == other.x && y == other.y;
            }
            bool operator!=(POS other) const {
                return !(*this == other);
            }
        };
        struct POS_3D {
            float x, y, z;

            POS_3D() = default;
            POS_3D(float x, float y, float z) : x(x), y(y), z(z) {};

            bool operator==(POS_3D other) const {
                return x == other.x && y == other.y && z == other.z;
            }
            bool operator!=(POS_3D other) const {
                return !(*this == other);
            }
        };

        struct COLOR {
            UINT32 rgb;
            FLOAT alpha;

            COLOR() = default;
            COLOR(UINT32 rgb, FLOAT alpha) : rgb(rgb), alpha(alpha) {};
            //COLOR(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha) : alpha(alpha) {}; // NEED: ARGB Color Mixer
        };

        struct ACCELERATION {
            double magnitude = 0;    // m/s^2
            double direction = 0;    // angle

            ACCELERATION() = default;
            ACCELERATION(double magnitude, double direction) :magnitude(magnitude), direction(direction) {};
        };
        struct VELOCITY {
            double magnitude = 0;    // m/s
            double direction = 0;    // angle

            VELOCITY() = default;
            VELOCITY(double magnitude, double direction) :magnitude(magnitude), direction(direction) {};
        };
        struct FORCE {
            double magnitude = 0;    // N
            double direction = 0;    // angle

            FORCE() = default;
            FORCE(double magnitude, double direction) :magnitude(magnitude), direction(direction) {};
        };

        struct VirtualKeyState {
            BOOL current = FALSE;
            BOOL last = FALSE;
        };

    }

}
