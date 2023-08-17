#pragma once
#include "ChaosEngine.h"

/* Define */

#define empty (float)0xFFFFFFFF // 4 bytes

#define SET_OPT(var, new_var) if(new_var != empty) var = new_var;   // Set optionally

// Window Message
#define WM_ENGINE_FRAME (WM_USER + 1)



namespace ChaosEngine {

    // Callback EngineProc
    typedef bool (CALLBACK* ENGINEPROC)();



    // Types defined
    namespace Type {

        struct WindowInitialProperty {
            int width = 800, height = 600;
            int x = CW_USEDEFAULT, y = CW_USEDEFAULT;
            LPSTR WndTitle = "New Game";
            HWND hWndParent = NULL;
        };
        struct EngineStartupProperty {
            ENGINEPROC pEngineExit;
            int FPS = 60;
        };

        struct SIZE {
            float width, height;

            SIZE() = default;

            SIZE(float width, float height) : width(width), height(height) {};
        };
        struct SIZE_3D {
            float length, width, height;

            SIZE_3D() = default;

            SIZE_3D(float length, float width, float height) : length(length), width(width), height(height) {};
        };

        struct POS {
            float x, y;

            POS() = default;

            POS(float x, float y) : x(x), y(y) {};
        };
        struct POS_3D {
            float x, y, z;

            POS_3D() = default;

            POS_3D(float x, float y, float z) : x(x), y(y), z(z) {};
        };

    }

}