#pragma once

#ifndef UNICODE
#define UNICODE
#endif


/* Libraries */
#pragma comment(lib,"DXGI.lib")
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"D2D1.lib")
#pragma comment(lib,"Dwrite.lib")
//#pragma comment(lib,"ChakraCore.lib")
//#pragma comment(lib,"OpenAL32.lib")


/* Dependances */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

#include <windows.h>
#include <windowsx.h>
#include <winuser.h>
#include <wincodec.h>
#include <wrl.h>
#include <dxgi.h>
#include <d2d1.h>
#include <dwrite.h>

//#include "ChakraCore/ChakraCore.h"
//#include "OpenAL/OpenAL.h"


/* Includes */

// common
#include "Common.h"
#include "Type.h"
#include "ResList.h"

#include "GraphicX.h"
#include "PhysicX.h"
#include "Stage.h"

#include "WindowX.h"
#include "DirectX.h"
#include "EngineX.h"


/* Source Codes */
#include "ResList.cpp"

#include "GraphicX.cpp"
#include "PhysicX.cpp"
#include "Stage.cpp"

#include "WindowX.cpp"
#include "DirectX.cpp"
#include "EngineX.cpp"