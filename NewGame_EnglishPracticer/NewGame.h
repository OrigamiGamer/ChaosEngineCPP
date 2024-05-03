#pragma once
#define UNICODE
//#define _GAME_DEV_

#pragma comment(lib,"ChaosEngine.lib")
#include "ChaosEngine.h"

using namespace std;
using namespace ChaosEngine;
using namespace Type;
using namespace Model;

#include "MainScene.h"
#include "DebugScene.h"

#include "MainScene.cpp"
#include "DebugScene.cpp"

BOOL GameMain();
BOOL GameExit();
