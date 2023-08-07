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
                LPRECT lpRect = NULL;
                if (!GetWindowRect(hWnd, lpRect)) return false;
                size.width = (float)(lpRect->right - lpRect->left);
                size.height = (float)(lpRect->bottom - lpRect->top);


                return true;
            };

        }

    }

}