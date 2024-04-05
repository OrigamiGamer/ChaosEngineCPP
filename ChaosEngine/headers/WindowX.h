#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace WindowX {

        namespace Prop {
            extern HWND hWnd;
            extern Type::SIZE Size;
            extern Type::POS Pos;
            extern Type::POS MousePos;
            extern Type::VirtKeyState VKeyStateBuffer[254];
            extern std::vector<int> VKeyInputBuffer;
        }

        HWND InitializeGameWindow(Type::WindowInitialProperty& WndProp);
        DWORD StartMessageLoop();
        VOID CALLBACK TimerProc_GameFrameUpdate(HWND hWnd, UINT p1, UINT_PTR p2, DWORD p3);
        LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    }

}