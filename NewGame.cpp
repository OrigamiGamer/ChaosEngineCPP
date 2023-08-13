#pragma once
#include "ChaosEngine\ChaosEngine.h"
#include <thread>

using namespace std;
using namespace ChaosEngine;

// Predefine
ENGINEPROC GameInit;
ENGINEPROC GameUpdate;
ENGINEPROC GameRender;
ENGINEPROC GameExit;

// Global
Engine* I_Engine = new Engine();

// Main
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {

    WindowInitialProperty WndProp;
    WndProp.WndTitle = "ChaosEngine Game Window Test";
    // WndProp.width = 1280;
    // WndProp.height = 720;

    EngineProcList ProcList;
    ProcList.GameInit = &GameInit;
    ProcList.GameUpdate = &GameUpdate;
    ProcList.GameRender = &GameRender;
    ProcList.GameExit = &GameExit;
    EngineStartupProperty EngineProp;
    EngineProp.ProcList = ProcList;

    I_Engine->Start(WndProp, EngineProp);
    I_Engine->Release();


    return 0;
};

LRESULT GameInit() {


    return 0;
};

LRESULT GameUpdate() {
    // OutputDebugString("aaaaaaaaaaaaaaaaaaaaaaaaaaa");

    return 0;
};

LRESULT GameRender() {


    return 0;
};

LRESULT GameExit() {


    return true;
};
