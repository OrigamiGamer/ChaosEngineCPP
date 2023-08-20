#pragma once
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


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
bool EngineExit();
