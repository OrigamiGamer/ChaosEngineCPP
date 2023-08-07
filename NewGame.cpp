#pragma once
#include "ChaosEngine\ChaosEngine.h"

using namespace ChaosEngine;
using namespace std;

#include "test.cpp"

HWND createWindow() {
    HWND hWnd;

    WNDCLASSEXA WndClassExA;
    WndClassExA.cbClsExtra = NULL;
    WndClassExA.cbWndExtra = NULL;
    WndClassExA.hbrBackground = NULL;
    WndClassExA.hCursor = NULL;
    WndClassExA.hIcon = NULL;
    WndClassExA.hInstance = NULL;
    WndClassExA.lpfnWndProc;
    WndClassExA.lpszClassName = "114514";
    // WndClassExA.lpszMenuName;
    // WndClassExA.style;

    ATOM hInstance = RegisterClassExA(&WndClassExA);

    hWnd = CreateWindowA(
        "114514",
        "114514aaa",
        NULL,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        NULL,
        0
    );

    cout << hWnd << endl << GetLastError() << endl;

    return hWnd;
}

void main() {
    HWND hWnd = createWindow();

    Engine* IEngine = new Engine();
    IEngine->Init(hWnd);

    cout << "Game runnning!" << endl;

    test();
};

