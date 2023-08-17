#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace WindowX {


        /* Function about DirectX */

        HRESULT InitDirectX(HWND hWnd);
        HRESULT ReleaseDirectX();



        /* Function about Windows */

        HWND InitWindow(Type::WindowInitialProperty WndProp);
        DWORD StartMessageLoop();

        // Callback TimerProc
        VOID CALLBACK TimerProc_GameFrameUpdate(HWND, UINT, UINT_PTR, DWORD);

        // Callback WndProc
        LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

    }

}
