#pragma once
#include "NewGame.h"


/* Only support single window */

// Main
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {

    static WindowInitialProperty WndProp;
    WndProp.WndTitle = L"ChaosEngine Game Window Test";
    // WndProp.width = 1280;
    // WndProp.height = 720;

    static EngineStartupProperty EngineProp;
    EngineProp.pGameExit = &GameExit;
    // EngineProp.FPS = 60;

    Stage::RegScene(main_scene);
    Stage::RegScene(debug_scene);

    Engine::Start(WndProp, EngineProp);
    Engine::Release();

    return 0;
};

BOOL GameExit() {
    if (MessageBox(Property::Window::hWnd, L"Please confirm to exit", L"Exit", MB_OKCANCEL) != IDOK)
        return FALSE;
    return TRUE;    // TRUE returned means confirm to exit the engine.
};
