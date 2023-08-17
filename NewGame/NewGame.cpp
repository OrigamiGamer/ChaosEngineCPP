#pragma once
#include "NewGame.h"


/* Only support single window */

// Main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    Engine::Stage::RegScene(&main_scene);
    Engine::Stage::RegScene(&debug_scene);

    static WindowInitialProperty WndProp;
    WndProp.WndTitle = (LPSTR)"ChaosEngine Game Window Test";
    // WndProp.width = 1280;
    // WndProp.height = 720;

    static EngineStartupProperty EngineProp;
    EngineProp.pEngineExit = &EngineExit;
    // EngineProp.FPS = 60;

    Engine::Start(&WndProp, &EngineProp);
    Engine::Release();

    return 0;
};

bool EngineExit() {
    if (MessageBox(Property::Window::hWnd, "Please confirm to exit", "Exit", MB_OKCANCEL) != IDOK)
        return false;
    return true;    // true returned means confirm to exit the engine.
};
