#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* Property */

    // It's used to store properties of Engine and Window at runtime.
    // 它用于在运行时储存 Engine 和 Window 的属性(Property)。
    namespace Property {

        /* Window */

        namespace Window {
            HWND hWnd = NULL;
            Type::SIZE Size;
            Type::POS Pos;
            Type::POS MousePos;

            void BindWindow(HWND new_hWnd) {
                hWnd = new_hWnd;

                // Immediately get basic attributes of the window
                RECT rect;
                if (!GetClientRect(hWnd, &rect)) return;

                /* Size */
                Size.width = (float)(rect.right - rect.left);
                Size.height = (float)(rect.bottom - rect.top);

                /* Pos */
                Pos.x = (float)rect.left;
                Pos.y = (float)rect.top;
            };

        };



        /* Engine */

        namespace Engine {
            Type::EngineStartupProperty* StartupProp = NULL;
                
        };

    }

}