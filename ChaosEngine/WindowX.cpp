#pragma once
#include "ChaosEngine.h"

#define WM_ENGINE_FRAME (WM_USER + 1)

namespace ChaosEngine {

    namespace WindowX {

        /* Function about DirectX */

        // Global
        ID2D1Factory* I_D2D_pFactory = NULL;


        HRESULT InitDirectX(HWND hWnd) {

            HRESULT hr = NULL;

            /* D2D */

            hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &I_D2D_pFactory);
            if (FAILED(hr)) return hr;

            D2D1_RENDER_TARGET_PROPERTIES RenderTarget_Properties{};
            //float hWndDpi = GetDpiForWindow(hWnd);
            //RenderTarget_Properties.dpiX = hWndDpi;
            //RenderTarget_Properties.dpiY = hWndDpi;
            RenderTarget_Properties.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
            RenderTarget_Properties.pixelFormat = { DXGI_FORMAT_R8G8B8A8_UNORM ,D2D1_ALPHA_MODE_PREMULTIPLIED };

            D2D1_HWND_RENDER_TARGET_PROPERTIES HwndRenderTarget_properties{};
            HwndRenderTarget_properties.hwnd = hWnd;
            HwndRenderTarget_properties.pixelSize = { (UINT32)Property::Window::Size.width,(UINT32)Property::Window::Size.height };
            HwndRenderTarget_properties.presentOptions = D2D1_PRESENT_OPTIONS_NONE;

            ID2D1HwndRenderTarget* HwndRenderTarget = NULL;
            hr = I_D2D_pFactory->CreateHwndRenderTarget(&RenderTarget_Properties, &HwndRenderTarget_properties, &HwndRenderTarget);
            if (FAILED(hr)) return hr;

            return hr;
        };

        // Release DirectX
        bool ReleaseDirectX() {
            /* D2D */
            SafeRelease(&I_D2D_pFactory);

            return true;
        };


        /* Function about WindowX */

        // Predefine
        LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
        VOID CALLBACK TimerProc_GameFrameUpdate(HWND, UINT, UINT_PTR, DWORD);

        // Initialize Window
        HWND InitWindow(WindowInitialProperty WndProp) {
            HWND hWnd;
            HINSTANCE hInst = GetModuleHandle(NULL);
            LPSTR ClassName = "ChaosGameWin";

            WNDCLASSEX WndClassEx{};
            WndClassEx.cbSize = sizeof(WNDCLASSEX);
            WndClassEx.hInstance = hInst;
            WndClassEx.lpszClassName = (LPCSTR)ClassName;
            WndClassEx.lpfnWndProc = WndProc;
            WndClassEx.style = CS_SAVEBITS | CS_DROPSHADOW;
            WndClassEx.cbClsExtra = 0;
            WndClassEx.cbWndExtra = 0;
            WndClassEx.hIcon = NULL;
            WndClassEx.hCursor = NULL;
            WndClassEx.hbrBackground = NULL;
            WndClassEx.lpszMenuName = NULL;
            WndClassEx.hIconSm = NULL;

            RegisterClassEx(&WndClassEx);

            hWnd = CreateWindowEx(
                (DWORD)NULL,
                (LPCSTR)ClassName,
                (LPCSTR)WndProp.WndTitle,
                WS_OVERLAPPEDWINDOW,
                WndProp.x, WndProp.y,
                WndProp.width, WndProp.height,
                WndProp.hWndParent,
                (HMENU)NULL,
                hInst,
                (LPVOID)NULL
            );
            if (hWnd == 0) {
                std::cout << "Initialize Window Failed! " << GetLastError() << std::endl;
                return 0;
            };

            ShowWindow(hWnd, SW_SHOW);
            UpdateWindow(hWnd);

            return hWnd;
        };

        // Start Message Loop
        DWORD StartMessageLoop() {
            MSG Msg;
            while (GetMessage(&Msg, NULL, 0, 0)) {
                TranslateMessage(&Msg);
                DispatchMessage(&Msg);
            };

            return (DWORD)Msg.wParam;
        };

        // Callback WndProc
        LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
            switch (uMsg) {

            case WM_CREATE:
                Property::Window::BindWindow(hWnd);
                // Property::Window::GetWinAttris();
                InitDirectX(hWnd);

                SetTimer(hWnd, 0, 1, (TIMERPROC)TimerProc_GameFrameUpdate);

                break;
            case WM_SIZE:
                Property::Window::Size.width = (float)LOWORD(lParam);
                Property::Window::Size.height = (float)HIWORD(lParam);

                break;
            case WM_MOVE:
                Property::Window::Pos.x = (float)LOWORD(lParam);
                Property::Window::Pos.y = (float)HIWORD(lParam);

                break;
            case WM_MOUSEMOVE:
                Property::Window::MousePos.x = (float)GET_X_LPARAM(lParam);
                Property::Window::MousePos.y = (float)GET_Y_LPARAM(lParam);

                break;
            case WM_ENGINE_FRAME:
                Property::Engine::ProcList.GameUpdate();    //

                break;
            case WM_CLOSE:
                DestroyWindow(hWnd);

                break;
            case WM_DESTROY:
                PostQuitMessage(0);

                break;
            default:
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            };

            return 0;
        };

        VOID CALLBACK TimerProc_GameFrameUpdate(HWND hWnd, UINT p1, UINT_PTR p2, DWORD p3) {
            SendMessage(hWnd, WM_ENGINE_FRAME, 0, 0);
        };

    }

}
