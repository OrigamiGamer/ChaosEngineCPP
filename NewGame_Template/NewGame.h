#pragma once
//#define UNICODE
//#define GAME_DEV

#include "ChaosEngine.h"
using namespace std;
using namespace ChaosEngine;
using namespace Type;
using namespace Model;


#include "MainScene.h"

#include "MainScene.cpp"


//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd);
BOOL GameMain();
BOOL GameExit();
