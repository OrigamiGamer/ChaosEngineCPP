#pragma once

// All is function is for single engine obj in a project.


/* Libraries */

#pragma comment(lib,"DXGI.lib")
#pragma comment(lib,"D2D1.lib") //#pragma comment(lib,"D3D12.lib")


/* Dependances */

#include <string>
#include <iostream>
#include <vector>
#include <windows.h>
#include <windowsx.h>
#include <wrl.h>
#include <dxgi.h>
#include <d2d1.h>   //#include <d3d12.h>
#include "ChakraCore/ChakraCore.h"
#include "FMOD_Studio/fmod_studio.hpp"
#include "JSON/json.hpp"


 /* Sources */

#include "Memory.h"
#include "Type.h"
#include "Property.h"
#include "WindowX.h"
#include "EngineX.h"
#include "res/ObjectList.h"
#include "Engine.h"

#include "Property.cpp"
#include "WindowX.cpp"
#include "EngineX.cpp"
#include "Engine.cpp"
