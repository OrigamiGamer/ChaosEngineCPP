#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace WindowX {

        /* Function about DirectX */

        // Global
        ID2D1Factory* pD2DFactory = NULL;
        ID2D1HwndRenderTarget* pHwndRenderTarget = NULL;
        IWICImagingFactory* pWICFactory = NULL;

        // Initialize DirectX
        HRESULT InitDirectX(HWND hWnd) {

            HRESULT hr = NULL;

            /* D2D */

            hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
            if (FAILED(hr)) return hr;

            D2D1_RENDER_TARGET_PROPERTIES RenderTarget_Properties{};
            //float hWndDpi = GetDpiForWindow(hWnd);
            //RenderTarget_Properties.dpiX = hWndDpi;
            //RenderTarget_Properties.dpiY = hWndDpi;
            RenderTarget_Properties.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
            RenderTarget_Properties.pixelFormat = { DXGI_FORMAT_R8G8B8A8_UNORM ,D2D1_ALPHA_MODE_PREMULTIPLIED };

            D2D1_HWND_RENDER_TARGET_PROPERTIES HwndRenderTarget_properties{};
            HwndRenderTarget_properties.hwnd = hWnd;
            HwndRenderTarget_properties.pixelSize = D2D1::SizeU((int)Property::Window::Size.width, (int)Property::Window::Size.height);
            HwndRenderTarget_properties.presentOptions = D2D1_PRESENT_OPTIONS_NONE;

            hr = pD2DFactory->CreateHwndRenderTarget(&RenderTarget_Properties, &HwndRenderTarget_properties, &pHwndRenderTarget);
            if (FAILED(hr)) return hr;

            /* WIC */

            hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWICFactory));
            if (FAILED(hr)) return hr;


            return hr;
        };

        // Release DirectX
        HRESULT ReleaseDirectX() {
            /* D2D */
            SafeRelease(&pD2DFactory);
            
            /* WIC */
            SafeRelease(&pWICFactory);

            pWICFactory->CreateBitmapFromMemory();

            return 0;
        };



        /* Function about Windows */

        // Initialize Window
        HWND InitWindow(Type::WindowInitialProperty* WndProp) {
            HWND hWnd;
            HINSTANCE hInst = GetModuleHandle(NULL);

            WNDCLASSEX WndClassEx;
            WndClassEx.cbSize = sizeof(WNDCLASSEX);
            WndClassEx.hInstance = hInst;
            WndClassEx.lpszClassName = L"ChaosGameWin";
            WndClassEx.lpfnWndProc = WndProc;
            WndClassEx.style = CS_HREDRAW | CS_VREDRAW; //CS_SAVEBITS | CS_DROPSHADOW;
            WndClassEx.cbClsExtra = 0;
            WndClassEx.cbWndExtra = 0;
            WndClassEx.hIcon = NULL;
            WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
            WndClassEx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            WndClassEx.lpszMenuName = NULL;
            WndClassEx.hIconSm = NULL;

            RegisterClassEx(&WndClassEx);

            hWnd = CreateWindow(
                L"ChaosGameWin",
                WndProp->WndTitle,
                WS_OVERLAPPEDWINDOW,
                WndProp->x, WndProp->y,
                WndProp->width, WndProp->height,
                WndProp->hWndParent,
                NULL,
                hInst,
                NULL
            );
            if (hWnd == 0) {
                std::wstring content = L"Initialize Window Failed! " + std::to_wstring(GetLastError());
                MessageBox(NULL, content.c_str(), L"ERROR", 0);
                return NULL;
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

        // Callback TimerProc
        VOID CALLBACK TimerProc_GameFrameUpdate(HWND hWnd, UINT p1, UINT_PTR p2, DWORD p3) {
            SendMessage(hWnd, WM_ENGINE_FRAME, 0, 0);
        };

        // Callback WndProc
        LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
            switch (uMsg) {

            case WM_ENGINE_FRAME:
                EngineX::EngineUpdate();    // Update
                EngineX::EngineRender();    // Render

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
            case WM_KEYDOWN:
                if (Property::Window::VirtKeyStateBuffer[wParam].current != TRUE)
                    Property::Window::VirtKeyStateBuffer[wParam].current = TRUE;

                break;
            case WM_KEYUP:
                if (Property::Window::VirtKeyStateBuffer[wParam].current != FALSE)
                    Property::Window::VirtKeyStateBuffer[wParam].current = FALSE;

                break;
            case WM_CREATE:
                Property::Window::BindWindow(hWnd);

                if (InitDirectX(hWnd) != S_OK) MessageBox(hWnd, L"Initialize Direct2D failed!", L"ERROR", 0);
                EngineX::EngineInit();  // Init

                SetTimer(hWnd, 0, 1, (TIMERPROC)TimerProc_GameFrameUpdate);

                break;
            case WM_CLOSE:
                if (EngineX::EngineExit() == TRUE)  // Exit
                    DestroyWindow(hWnd);

                break;
            case WM_DESTROY:
                UnregisterClass(L"ChaosGameWin", NULL);
                PostQuitMessage(0);

                break;
            default:
                return DefWindowProc(hWnd, uMsg, wParam, lParam);

            };

            return 0;
        };

    }

}
