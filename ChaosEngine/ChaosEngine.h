#pragma once
#define UNICODE
#define _UNICODE

// All is function is for single engine obj in single project.

/* Libraries */
//#pragma comment(lib,"DXGI.lib")
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"D2D1.lib")	//#pragma comment(lib,"D3D12.lib")
#pragma comment(lib,"Dwrite.lib")

/* Dependances */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <windowsx.h>
#include <winuser.h>
#include <wrl.h>
#include <dxgi.h>
#include <d2d1.h>	//#include <d3d12.h>
#include <dwrite.h>
#include <wincodec.h>

#include "ChakraCore/ChakraCore.h"
#include "OpenAL/alcpp.h"

/* Headers */
#include "headers/Utils.h"
#include "headers/Type.h"
#include "res/ResList.h"

#include "headers/DirectX.h"
#include "headers/WindowX.h"
#include "headers/GraphicX.h"

#include "headers/PhysicX.h"
#include "headers/Stage.h"

#include "headers/EngineX.h"


/* Sources */
#ifndef GAME_DEV
#include "res/ResList.cpp"

#include "DirectX.cpp"
#include "WindowX.cpp"
#include "GraphicX.cpp"

#include "PhysicX.cpp"
#include "Stage.cpp"

#include "EngineX.cpp"


#endif
