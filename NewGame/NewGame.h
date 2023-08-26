#pragma once
//#define UNICODE
//#define GAME_DEV

#include "ChaosEngine.h"
using namespace std;
using namespace ChaosEngine;
using namespace Type;
using namespace Model;

#include "MainScene.h"
#include "DebugScene.h"

#include "MainScene.cpp"
#include "DebugScene.cpp"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd);
BOOL EngineExit();
