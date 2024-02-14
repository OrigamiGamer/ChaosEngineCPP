#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace WindowX {

        /* Function about Windows */

        HWND InitWindow(Type::WindowInitialProperty* WndProp);
        DWORD StartMessageLoop();

        // Callback TimerProc
        VOID CALLBACK TimerProc_GameFrameUpdate(HWND, UINT, UINT_PTR, DWORD);

        // Callback WndProc
        LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


        /* Function about DirectX */

        // Global
        extern ID2D1Factory* pD2DFactory;
        extern ID2D1HwndRenderTarget* pHwndRenderTarget;
        extern IWICImagingFactory* pWICFactory;
        extern IDWriteFactory* pDWriteFactory;

        HRESULT InitDirectX(HWND hWnd);
        HRESULT ReleaseDirectX();

    }

}
