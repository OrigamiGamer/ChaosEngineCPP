#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    /* Property */
    // It's used to store properties of Engine and Window at runtime. // ������������ʱ���� Engine �� Window ������(Property)��
    namespace Property {

        using namespace std;

        /* Window */
        namespace Window {
            HWND hWnd = NULL;
            Type::SIZE Size;
            Type::POS Pos;
            Type::POS MousePos;

            void BindWindow(HWND new_hWnd);

            // Get the most attributes of window
            bool GetWinAttris();

        };

        /* Engine */
        namespace Engine {
            EngineProcList ProcList;



        };

    }

}