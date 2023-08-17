#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* Property */

    // It's used to store properties of Engine and Window at runtime.
    // 它用于在运行时储存 Engine 和 Window 的属性(Property)。
    namespace Property {

        /* Window */

        namespace Window {
            void BindWindow(HWND new_hWnd);

            // Get the most attributes of window
            bool GetWinAttris();

        };



        /* Engine */

        namespace Engine {

        };

    }

}