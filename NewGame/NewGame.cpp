#pragma once
#include "NewGame.h"


/* Only support single window */

// Main

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

    WindowInitialProperty WndProp;
    WndProp.WndTitle = (LPSTR)"ChaosEngine Game Window Test";
    // WndProp.width = 1280;
    // WndProp.height = 720;

    EngineStartupProperty EngineProp;
    // EngineProp.FPS = 60;

    Engine::Start(&WndProp, &EngineProp);
    Engine::Release();

    return 0;
};
