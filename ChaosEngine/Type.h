#pragma once
#include "ChaosEngine.h"

/* Define */

#define empty (float)0xFFFFFFFF // 4 bytes

#define SET_OPT(var, new_var) if(new_var != empty) var = new_var;   // Set optionally


namespace ChaosEngine {

    struct WindowInitialProperty {
        int width = 800, height = 600;
        int x = CW_USEDEFAULT, y = CW_USEDEFAULT;
        LPSTR WndTitle = "New Game";
        HWND hWndParent = 0;
    };

    typedef LRESULT(CALLBACK ENGINEPROC)();

    struct EngineProcList {
        ENGINEPROC* GameInit = NULL;
        ENGINEPROC* GameUpdate = NULL;
        ENGINEPROC* GameRender = NULL;
        ENGINEPROC* GameExit = NULL;
    };

    struct EngineStartupProperty {
        EngineProcList ProcList;
    };


    namespace Type {

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

        // Engine* engine = new Engine();

    }

}