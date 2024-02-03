#pragma once
#include "ChaosEngine.h"

/* Define */
#define emptyf (float)0xFFFFFFFF            // 4 bytes
#define emptyd (double)0xFFFFFFFFFFFFFFFF   // 8 bytes

#define SET_OPT(var, new_var) if(new_var != empty) var = new_var;   // Set optionally

// Window Message
#define WM_ENGINE_FRAME (WM_USER + 1)



namespace ChaosEngine {

    // Type defines
    namespace Type {

        // Callback EngineProc
        typedef BOOL(CALLBACK* ENGINEPROC)();

        // Initial Property
        struct WindowInitialProperty {
            int width = 800, height = 600;
            int x = CW_USEDEFAULT, y = CW_USEDEFAULT;
            LPWSTR WndTitle = L"New Game";
            HWND hWndParent = NULL;
        };
        struct EngineStartupProperty {
            ENGINEPROC pGameMain;
            ENGINEPROC pGameExit;
            int FPS = 60;
        };

        // Basic Type
        struct SIZE {
            double width, height;

            SIZE() = default;
            SIZE(double width, double height) : width(width), height(height) {};
        };
        struct SIZE_3D {
            double length, width, height;

            SIZE_3D() = default;
            SIZE_3D(double length, double width, double height) : length(length), width(width), height(height) {};
        };

        struct POS {
            double x = 0, y = 0;

            POS() = default;
            POS(double x, double y) : x(x), y(y) {};
        };
        struct POS_3D {
            double x, y, z;

            POS_3D() = default;
            POS_3D(double x, double y, double z) : x(x), y(y), z(z) {};
        };

        struct COLOR {
            BYTE rgb;
            float alpha;

            COLOR() = default;
            COLOR(BYTE rgb, float alpha) : rgb(rgb), alpha(alpha) {};
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
