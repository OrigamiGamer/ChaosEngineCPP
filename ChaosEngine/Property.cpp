#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace Property {

        namespace Window {
            HWND hWnd;
            Type::Size2D size;

            void BindWindow(HWND new_hWnd) {
                hWnd = hWnd;
            };

            /* Get Window Attributes */
            bool GetWinAttris() {

                // Size //
                RECT rect;
                if (!GetWindowRect(hWnd, &rect)) return false;
                size.width = (float)(rect.right - rect.left);
                size.height = (float)(rect.bottom - rect.top);


                return true;
            };

        }

    }

}