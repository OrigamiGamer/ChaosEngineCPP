#pragma once


/* Libraries */

#pragma comment(lib,"DXGI.lib")
#pragma comment(lib,"D2D1.lib") //#pragma comment(lib,"D3D12.lib")
#pragma comment(lib,"ChakraCore.lib")   // #pragma comment(lib,"../ChaosEngine/lib/ChakraCore.lib")


/* Dependances */

#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <wrl.h>
#include <dxgi.h>
//#include <d3d12.h>
#include <d2d1.h>
#include "lib\ChakraCore\ChakraCore.h"


 /* Sources */

#include "Memory.h"
#include "Type.h"
#include "Model.h"
#include "Property.cpp"
#include "WindowX.cpp"
#include "Engine.cpp"
