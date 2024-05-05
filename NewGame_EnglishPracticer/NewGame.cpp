#include "NewGame.h"

/* Only support single window */

// Main
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

    static WindowInitialProperty WndProp;
    WndProp.WndTitle = L"ChaosEngine Game Window Test (You are the stone)";
    WndProp.width = 1280;
    WndProp.height = 720;

    static EngineStartupProperty EngineProp;
    EngineProp.pGameMain = &GameMain;
    EngineProp.pGameExit = &GameExit;
    // EngineProp.FPS = 60;

    EngineX::Initialize(EngineProp, WndProp);

    return 0;
};

BOOL GameMain() {
    Stage::RegScene(scene_main);
    Stage::RegScene(scene_debug);

    return TRUE;
}

BOOL GameExit() {
    if (MessageBox(WindowX::Prop::hWnd, L"Please confirm to exit", L"Exit", MB_OKCANCEL) != IDOK)
        return FALSE;
    return TRUE;    // TRUE returned means confirm to exit the engine.
};
