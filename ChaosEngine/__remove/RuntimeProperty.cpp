#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace RuntimeProperty {

        WindowRuntimeProperty::WindowRuntimeProperty() {
            hWnd = nullptr;
            size;
            pos;
            mousePos;
            VirtKeyStateBuffer;
            VirtKeyInputBuffer;
        }

        void WindowRuntimeProperty::BindWindow(HWND new_hWnd) {
            hWnd = new_hWnd;

            // Immediately get basic attributes of the window
            RECT rect;
            if (!GetClientRect(hWnd, &rect)) return;

            size.width = (float)(rect.right - rect.left);
            size.height = (float)(rect.bottom - rect.top);
            pos.x = (float)rect.left;
            pos.y = (float)rect.top;
        }

        EngineRuntimeProperty::EngineRuntimeProperty() {
            pStartupProp = nullptr;
            lastTime = 0;
            deltaTime = 0;
        }

    }

}