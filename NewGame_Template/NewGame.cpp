#pragma once
#include "NewGame.h"


/* Only support single window */

// Main
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {

    static WindowInitialProperty WndProp;
    WndProp.WndTitle = L"ChaosEngine Game Window Test";
    WndProp.width = 1600;
    WndProp.height = 900;

    static EngineStartupProperty EngineProp;
    EngineProp.pGameMain = &GameMain;
    EngineProp.pGameExit = &GameExit;
    // EngineProp.FPS = 60;

    EngineX::Initialize(EngineProp, WndProp);

    return 0;
};

BOOL GameMain() {
    Stage::RegScene(scene_main);

    return TRUE;
}

BOOL GameExit() {
    if (MessageBox(WindowX::Prop::hWnd, L"Please confirm to exit", L"Exit", MB_OKCANCEL) != IDOK)
        return FALSE;
    return TRUE;    // TRUE returned means confirm to exit the engine.
};
