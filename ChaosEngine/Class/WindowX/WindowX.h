#pragma once



#include "Class/Class.h"



// GLFW

#define GLFW_EXPOSE_NATIVE_WIN32

#include "ExternalLibrary/GLFW/glfw3.h"
#include "ExternalLibrary/GLFW/glfw3native.h"



// WindowX

namespace Chaos::WindowX {

}


#include "Class/WindowX/WindowManager.h"

#include "Class/WindowX/KeyStateBuffer.h"

#include "Class/WindowX/KeyState.h"

#include "Class/WindowX/HotKey.h"

#include "Class/WindowX/WindowStartupProperty.h"

#include "Class/WindowX/Window.h"
