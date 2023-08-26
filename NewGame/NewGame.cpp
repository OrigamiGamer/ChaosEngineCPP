#pragma once
#include "NewGame.h"


/* Only support single window */

// Main
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
    Engine::Stage::RegScene(main_scene);
    Engine::Stage::RegScene(debug_scene);

    static WindowInitialProperty WndProp;
    WndProp.WndTitle = L"ChaosEngine Game Window Test";
    // WndProp.width = 1280;
    // WndProp.height = 720;

    static EngineStartupProperty EngineProp;
    EngineProp.pEngineExit = &EngineExit;
    // EngineProp.FPS = 60;

    Engine::Start(WndProp, EngineProp);
    Engine::Release();

    return 0;
};

BOOL EngineExit() {
    if (MessageBox(Property::Window::hWnd, L"Please confirm to exit", L"Exit", MB_OKCANCEL) != IDOK)
        return FALSE;
    return TRUE;    // TRUE returned means confirm to exit the engine.
};
