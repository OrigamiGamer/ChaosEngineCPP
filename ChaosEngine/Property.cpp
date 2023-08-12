#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* Property */
    // It's used to store properties of Engine and Window at runtime. // 它用于在运行时储存 Engine 和 Window 的属性(Property)。
    namespace Property {

        using namespace std;

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

                /* MousePos */
                // MOUSEMOVEPOINT mp_in{};
                // MOUSEMOVEPOINT mp_out[64];
                // mp_in.x = (int)Window::Pos.x;
                // mp_in.y = (int)Window::Pos.y;
                // int n = GetMouseMovePointsEx(sizeof(MOUSEMOVEPOINT), &mp_in, &mp_out[0], 64, GMMP_USE_DISPLAY_POINTS);

                // for (int i = 0; i < n; i++) {
                //     if (mp_out[i].x > 32767)
                //         mp_out[i].x -= 65536;
                //     if (mp_out[i].y > 32767)
                //         mp_out[i].y -= 65536;

                //     cout << i << " -> " << mp_out[i].x << ", " << mp_out[i].y << endl;
                // };


                return true;
            };

        }

        /* Engine */
        namespace Engine {
            ENGINEPROC* GameInit = NULL;
            ENGINEPROC* GameUpdate = NULL;
            ENGINEPROC* GameRender = NULL;
            ENGINEPROC* GameExit = NULL;



        }

    }

}