#pragma once
#include "ChaosEngine.h"

#define WM_ENGINE_FRAME (WM_USER + 1)

namespace ChaosEngine {

    namespace WindowX {

        namespace Prop {
            HWND hWnd = nullptr;
            Type::SIZE Size;
            Type::POS Pos;
            Type::POS MousePos;
            Type::POS MouseOffsetPos;
            Type::VirtualKeyState VirtKeyStateBuffer[254];
            std::vector<int> VirtKeyInputBuffer;
        }

        // Initialize Game Window
        HWND InitializeGameWindow(Type::WindowInitialProperty& WndProp) {
            HINSTANCE hInst = GetModuleHandle(NULL);

            WNDCLASSEX WndClassEx{};
            WndClassEx.cbSize = sizeof(WNDCLASSEX);
            WndClassEx.hInstance = hInst;
            WndClassEx.lpszClassName = L"ChaosGameWin";
            WndClassEx.lpfnWndProc = WindowX::WndProc;
            WndClassEx.style = CS_HREDRAW | CS_VREDRAW; //CS_SAVEBITS | CS_DROPSHADOW;
            WndClassEx.cbClsExtra = 0;
            WndClassEx.cbWndExtra = 0;
            WndClassEx.hIcon = NULL;
            WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
            WndClassEx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            WndClassEx.lpszMenuName = NULL;
            WndClassEx.hIconSm = NULL;
            RegisterClassEx(&WndClassEx);

            Prop::hWnd = CreateWindowEx(
                NULL,
                L"ChaosGameWin",
                WndProp.WndTitle.c_str(),
                WS_OVERLAPPEDWINDOW,
                WndProp.x, WndProp.y,
                WndProp.width, WndProp.height,
                WndProp.hWndParent,
                NULL,
                hInst,
                nullptr
            );
            if (Prop::hWnd == 0) {
                std::wstring content = L"Initialize Window Failed! " + std::to_wstring(GetLastError());
                MessageBox(NULL, content.c_str(), L"ERROR", 0);
                return NULL;
            }

            ShowWindow(Prop::hWnd, SW_SHOW);
            UpdateWindow(Prop::hWnd);
            return Prop::hWnd;
        }

        // Start Message Loop
        DWORD StartMessageLoop() {
            MSG Msg;
            while (GetMessage(&Msg, NULL, 0, 0)) {
                TranslateMessage(&Msg);
                DispatchMessage(&Msg);
            };
            return (DWORD)Msg.wParam;
        }

        // Callback TimerProc
        VOID CALLBACK TimerProc_GameFrameUpdate(HWND hWnd, UINT p1, UINT_PTR p2, DWORD p3) {
            SendMessage(hWnd, WM_ENGINE_FRAME, 0, 0);
        }

        // Callback WndProc
        LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
            switch (uMsg) {

            case WM_ENGINE_FRAME:
                EngineX::EngineUpdate();    // Update
                EngineX::EngineRender();    // Render

                break;
            case WM_SIZE:
                WindowX::Prop::Size.width = (float)LOWORD(lParam);
                WindowX::Prop::Size.height = (float)HIWORD(lParam);

                break;
            case WM_MOVE:
                WindowX::Prop::Pos.x = (float)LOWORD(lParam);
                WindowX::Prop::Pos.y = (float)HIWORD(lParam);

                break;
            case WM_MOUSEMOVE:
                WindowX::Prop::MousePos.x = (float)GET_X_LPARAM(lParam);
                WindowX::Prop::MousePos.y = (float)GET_Y_LPARAM(lParam);
                
                break;
            case WM_KEYDOWN:
                if (WindowX::Prop::VirtKeyStateBuffer[wParam].current != TRUE)
                    WindowX::Prop::VirtKeyStateBuffer[wParam].current = TRUE;

                break;
            case WM_KEYUP:
                if (WindowX::Prop::VirtKeyStateBuffer[wParam].current != FALSE)
                    WindowX::Prop::VirtKeyStateBuffer[wParam].current = FALSE;

                break;
            case WM_CHAR:
                WindowX::Prop::VirtKeyInputBuffer.push_back(static_cast<int>(wParam));

                break;
            case WM_CREATE:
                RECT rect;
                GetClientRect(hWnd, &rect);
                Prop::Size.width = (float)(rect.right - rect.left);
                Prop::Size.height = (float)(rect.bottom - rect.top);
                Prop::Pos.x = (float)rect.left;
                Prop::Pos.y = (float)rect.top;

                if (DirectX::InitializeDirectX(hWnd) != S_OK) MessageBox(hWnd, L"Initialize Direct2D failed!", L"ERROR", 0);

                EngineX::EngineInit();   // Init

                SetTimer(hWnd, 0, 1, (TIMERPROC)TimerProc_GameFrameUpdate);

                break;
            case WM_CLOSE:
                if (EngineX::EngineExit() == TRUE)  // Exit
                    DestroyWindow(hWnd);

                break;
            case WM_DESTROY:
                DirectX::ReleaseDirectX();

                UnregisterClass(L"ChaosGameWin", NULL);
                PostQuitMessage(0);

                break;
            default:
                return DefWindowProc(hWnd, uMsg, wParam, lParam);

            }

            return NULL;
        }

    }

}