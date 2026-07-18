#pragma once



#include "chaos/chaos.h"



// GLFW

#define GLFW_EXPOSE_NATIVE_WIN32

#include "Dependences/Static/glfw/glfw3.h"
#include "Dependences/Static/glfw/glfw3native.h"



// windows

namespace chaos::windows {

}


#include "chaos/windows/WindowManager.h"

#include "chaos/windows/KeyStateBuffer.h"

#include "chaos/windows/KeyState.h"

#include "chaos/windows/HotKey.h"

#include "chaos/windows/WindowStartupProperty.h"

#include "chaos/windows/Window.h"
