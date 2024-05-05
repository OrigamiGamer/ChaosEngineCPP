#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    //namespace WindowX {

    //    // Start Message Loop
    //    DWORD StartMessageLoop() {
    //        MSG Msg;
    //        while (GetMessage(&Msg, NULL, 0, 0)) {
    //            TranslateMessage(&Msg);
    //            DispatchMessage(&Msg);
    //        };
    //        return (DWORD)Msg.wParam;
    //    };

    //    // Callback TimerProc
    //    VOID CALLBACK TimerProc_GameFrameUpdate(HWND hWnd, UINT p1, UINT_PTR p2, DWORD p3) {
    //        SendMessage(hWnd, WM_ENGINE_FRAME, 0, 0);
    //    };

    //    // Callback WndProc
    //    LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    //        switch (uMsg) {

    //        case WM_ENGINE_FRAME:
    //            EngineX::EngineUpdate();    // Update
    //            EngineX::EngineRender();    // Render

    //            break;
    //        case WM_SIZE:
    //            Properties::Window::Size.width = (float)LOWORD(lParam);
    //            Properties::Window::Size.height = (float)HIWORD(lParam);

    //            break;
    //        case WM_MOVE:
    //            Properties::Window::Pos.x = (float)LOWORD(lParam);
    //            Properties::Window::Pos.y = (float)HIWORD(lParam);

    //            break;
    //        case WM_MOUSEMOVE:
    //            Properties::Window::MousePos.x = (float)GET_X_LPARAM(lParam);
    //            Properties::Window::MousePos.y = (float)GET_Y_LPARAM(lParam);

    //            break;
    //        case WM_KEYDOWN:
    //            if (Properties::Window::VirtKeyStateBuffer[wParam].current != TRUE)
    //                Properties::Window::VirtKeyStateBuffer[wParam].current = TRUE;

    //            break;
    //        case WM_KEYUP:
    //            if (Properties::Window::VirtKeyStateBuffer[wParam].current != FALSE)
    //                Properties::Window::VirtKeyStateBuffer[wParam].current = FALSE;

    //            break;
    //        case WM_CHAR:
    //            Properties::Window::VirtKeyInputBuffer.push_back(static_cast<int>(wParam));

    //            break;
    //        case WM_CREATE:
    //            Properties::Window::BindWindow(hWnd);

    //            if (InitDirectX(hWnd) != S_OK) MessageBox(hWnd, L"Initialize Direct2D failed!", L"ERROR", 0);
    //            EngineX::EngineInit();  // Init

    //            SetTimer(hWnd, 0, 1, (TIMERPROC)TimerProc_GameFrameUpdate);

    //            break;
    //        case WM_CLOSE:
    //            if (EngineX::EngineExit() == TRUE)  // Exit
    //                DestroyWindow(hWnd);

    //            break;
    //        case WM_DESTROY:
    //            UnregisterClass(L"ChaosGameWin", NULL);
    //            PostQuitMessage(0);

    //            break;
    //        default:
    //            return DefWindowProc(hWnd, uMsg, wParam, lParam);

    //        };

    //        return 0;
    //    };

    //}





    /* Compiler Definitions */
#define WM_ENGINE_FRAME (WM_USER + 1)




    

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
            //EngineX::EngineUpdate();    // Update
            //EngineX::EngineRender();    // Render

            break;
        case WM_SIZE:

            break;
        case WM_MOVE:

            break;
        case WM_MOUSEMOVE:

            break;
        case WM_KEYDOWN:

            break;
        case WM_KEYUP:

            break;
        case WM_CHAR:

            break;
        case WM_CREATE:

            break;
        case WM_CLOSE:
            //if (EngineX::EngineExit() == TRUE)  // Exit
                //DestroyWindow(hWnd);

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



    namespace Engine {

        Type::EngineStartupProperty* pStartupProp = nullptr;
        long double lastTime = 0;
        long double deltaTime = 0;
        Window window;


        HRESULT Initialize(Type::EngineStartupProperty& EngineProp) {
            HRESULT hr = S_OK;
            pStartupProp = &EngineProp;
            hr = DirectX::InitializeDirectX(); if (FAILED(hr)) return hr;

            return TRUE;
        };

        HRESULT CreateGameWindow(Type::WindowInitialProperty& WndProp) {
            HRESULT hr = S_OK;
            HWND hWnd = window.InitializeGameWindow(WndProp);
            hr = DirectX::CreateRenderTarget(hWnd); if (FAILED(hr)) return hr;

            return TRUE;
        };

        // Engine Init
        LRESULT EngineInit() {

            return S_OK;
        };

        // Engine Update
        LRESULT EngineUpdate() {

            return S_OK;
        };

        // Engine Render
        LRESULT EngineRender() {

            return S_OK;
        };

        // Engine Exit
        LRESULT EngineExit() {

            return TRUE;    // TRUE returned means confirm exiting.
        };

        BOOL Release() {
            DirectX::ReleaseDirectX();

            return TRUE;
        };

    }
    
}
