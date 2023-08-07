#pragma once
#include "ChaosEngine\ChaosEngine.h"

using namespace ChaosEngine;
using namespace std;

#include "test.cpp"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND CreateWindowDemo();

void main() {
    HWND hWnd = CreateWindowDemo();

    Engine* IEngine = new Engine();
    IEngine->Init(hWnd);

    cout << "Game runnning!" << endl;

    test();
};

HWND CreateWindowDemo() {
    HWND hWnd;
    HINSTANCE hInst = GetModuleHandleA("114514");
    LPSTR WindowName = "Window - 114514";
    LPSTR ClassName = "114514";

    WNDCLASSEXA WndClassExA;
    WndClassExA.cbClsExtra = NULL;
    WndClassExA.cbWndExtra = NULL;
    WndClassExA.hbrBackground = NULL;
    WndClassExA.hCursor = NULL;
    WndClassExA.hIcon = NULL;
    WndClassExA.hInstance = hInst;
    WndClassExA.lpfnWndProc = WndProc;
    WndClassExA.lpszClassName = ClassName;
    // WndClassExA.lpszMenuName;
    // WndClassExA.style;

    RegisterClassExA(&WndClassExA);

    hWnd = CreateWindowExA(
        NULL,
        ClassName,
        WindowName,
        NULL,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInst,
        0
    );

    cout << hWnd << endl << GetLastError() << endl;

    return hWnd;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    return 0;
};
