#pragma once
#define UNICODE
//#define _UNICODE
// All is function is for single engine obj in single project.

/* Libraries */
//#pragma comment(lib,"DXGI.lib")
#pragma comment(lib,"D2D1.lib")	//#pragma comment(lib,"D3D12.lib")
#pragma comment(lib,"Dwrite.lib")

/* Dependances */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <windowsx.h>
#include <wrl.h>
#include <dxgi.h>
#include <d2d1.h>	//#include <d3d12.h>
#include <dwrite.h>
#include <wincodec.h>

#include "ChakraCore/ChakraCore.h"
#include "FMOD_Studio/fmod_studio.hpp"
#include "JSON/json.hpp"

/* Headers */
#include "headers/Utils.h"
#include "headers/Type.h"
#include "headers/Property.h"
#include "res/ResList.h"
#include "headers/WindowX.h"
#include "headers/EngineX.h"
#include "headers/PhysicX.h"
#include "headers/Engine.h"
#include "headers/Stage.h"
#include "headers/GraphicX.h"

/* Sources */
#ifndef GAME_DEV
#include "Property.cpp"
#include "res/ResList.cpp"
#include "WindowX.cpp"
#include "EngineX.cpp"
#include "PhysicX.cpp"
#include "Engine.cpp"
#include "Stage.cpp"
#include "GraphicX.cpp"

#endif
