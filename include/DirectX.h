#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace DirectX {

        extern ID2D1Factory* pD2DFactory;
        extern IWICImagingFactory* pWICFactory;
        extern IDWriteFactory* pDWriteFactory;
        extern ID2D1HwndRenderTarget* pHwndRenderTarget;

        HRESULT InitializeDirectX(HWND hWnd);
        HRESULT CreateRenderTarget(HWND hWnd);
        HRESULT ReleaseDirectX();

    }

}