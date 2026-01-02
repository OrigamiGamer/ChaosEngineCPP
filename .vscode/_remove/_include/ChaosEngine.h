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
#include <map>
#include <chrono>
#include <math.h>

// 3rd Libraries
#include "DirectX.h"
#include "DirectX.cpp"
//#include "ChakraCore/ChakraCore.h"
//#include "OpenAL/OpenAL.h"


/* Includes */
// common
#include "Util.h"
#include "Type.h"
#include "ResList.h"

#include "Graphics.h"
#include "Physic.h"
#include "Stage.h"

#include "WindowX.h"
#include "EngineX.h"


// Source Codes
#include "ResList.cpp"

#include "Graphics.cpp"
#include "Physic.cpp"
#include "Stage.cpp"

#include "WindowX.cpp"
#include "EngineX.cpp"
