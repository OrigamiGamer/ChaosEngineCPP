#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* Property */

    // It's used to store properties of Engine and Window at runtime.
    // 它用于在运行时储存 Engine 和 Window 的属性(Property)。
    namespace Properties {

        /* Window */

        namespace Window {
            extern HWND hWnd;
            extern Type::SIZE Size;
            extern Type::POS Pos;
            extern Type::POS MousePos;
            extern Type::VirtualKeyState VirtKeyStateBuffer[254];
            extern std::vector<int> VirtKeyInputBuffer;

            void BindWindow(HWND new_hWnd);

        };



        /* Engine */

        namespace Engine {
            extern Type::EngineStartupProperty* StartupProp;
            extern long double LastTime;
            extern long double DeltaTime;
        };

    }

}
