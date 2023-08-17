#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* Property */

    // It's used to store properties of Engine and Window at runtime.
    // ������������ʱ���� Engine �� Window ������(Property)��
    namespace Property {

        /* Window */

        namespace Window {
            HWND hWnd = NULL;
            Type::SIZE Size;
            Type::POS Pos;
            Type::POS MousePos;

            void BindWindow(HWND new_hWnd) {
                hWnd = new_hWnd;
            };

            // Get the most attributes of window
            bool GetWinAttris() {
                RECT rect;
                if (!GetClientRect(hWnd, &rect)) return false;

                /* Size */
                Size.width = (float)(rect.right - rect.left);
                Size.height = (float)(rect.bottom - rect.top);

                /* Pos */
                Pos.x = (float)rect.left;
                Pos.y = (float)rect.top;


                return true;
            };

        };



        /* Engine */

        namespace Engine {
            Type::EngineStartupProperty* StartupProp = NULL;

        };

    }

}