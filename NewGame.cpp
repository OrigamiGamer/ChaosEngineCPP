#pragma once
#include "ChaosEngine\ChaosEngine.h"
#include <thread>

using namespace ChaosEngine;
using namespace std;

#include "test.cpp"

// Define Processes
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
DWORD LoadWindow();
void Debug(HWND hWnd);


// Main
int main() {
    return LoadWindow();
};

DWORD LoadWindow() {
    HWND hWnd;
    HINSTANCE hInst = GetModuleHandleA(NULL);
    LPSTR ClassName = "ChaosGameWin";
    LPSTR WindowName = "114514";

    WNDCLASSEXA WndClassExA{};
    WndClassExA.cbSize = sizeof(WNDCLASSEX);
    WndClassExA.hInstance = hInst;
    WndClassExA.lpszClassName = ClassName;
    WndClassExA.lpfnWndProc = WndProc;
    WndClassExA.style = CS_SAVEBITS | CS_DROPSHADOW;
    WndClassExA.cbClsExtra = 0;
    WndClassExA.cbWndExtra = 0;
    WndClassExA.hIcon = NULL;
    WndClassExA.hCursor = NULL;
    WndClassExA.hbrBackground = NULL;
    WndClassExA.lpszMenuName = NULL;
    WndClassExA.hIconSm = NULL;

    RegisterClassExA(&WndClassExA);
    cout << "RegClass -> " << GetLastError() << endl;

    hWnd = CreateWindowExA(
        NULL,
        ClassName,
        WindowName,
        WS_OVERLAPPEDWINDOW,
        0, 0,
        1280, 720,
        NULL,
        NULL,
        hInst,
        NULL
    );
    if (hWnd == NULL) return GetLastError();

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    // Start Message Loop
    MSG Msg;
    while (GetMessageA(&Msg, hWnd, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
        if (Msg.message == WM_QUIT)
            return (DWORD)Msg.wParam;
    };
    cout << "Process ended" << endl;

    return (DWORD)Msg.wParam;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        cout << "Window -> Created" << endl;
        Debug(hWnd);
        
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        
        break;
    default:
        return DefWindowProcA(hWnd, uMsg, wParam, lParam);
    };
    return 0;
};

void Debug(HWND hWnd) {
    Engine* I_Engine = new Engine();
    I_Engine->Init(hWnd);


    test();
};
