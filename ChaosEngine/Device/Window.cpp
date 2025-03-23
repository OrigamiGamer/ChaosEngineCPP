#pragma once

#include "Common.h"

namespace Chaos::Device {
    Window::Window(Device::Engine* new_engine)
    {
        this->engine.refer(new_engine);
        this->INIT("Window");
        this->_glfwWindow = nullptr;
    }

    Window::~Window()
    {
        if (this->_glfwWindow != nullptr) glfwDestroyWindow(this->_glfwWindow);
    }

    bool Window::initialize(WindowProperty* new_windowProp)
    {
        if (new_windowProp != nullptr) {
            // User's window property
            this->_glfwWindow = glfwCreateWindow(
                new_windowProp->size.x,
                new_windowProp->size.y,
                new_windowProp->title.c_str(),
                nullptr,
                nullptr
            );
            if (!this->_glfwWindow) return false;

            glfwSetWindowPos(
                this->_glfwWindow,
                new_windowProp->pos.x,
                new_windowProp->pos.y
            );
        }
        else {
            // Default window property
            this->_glfwWindow = glfwCreateWindow(
                800,
                600,
                "Window",
                nullptr,
                nullptr
            );
            if (!this->_glfwWindow) return false;
        }

        // Register the window created to WindowManager
        WindowManager::registerWindow(this);


        // Window Callback Functions:

        // Window Pos
        glfwSetWindowPosCallback(this->_glfwWindow, WindowManager::_s_onWindowPos);

        // Window Size
        glfwSetWindowSizeCallback(this->_glfwWindow, WindowManager::_s_onWindowSize);

        // Window Close
        glfwSetWindowCloseCallback(this->_glfwWindow, WindowManager::_s_onWindowClose);

        // Window Focus
        glfwSetWindowFocusCallback(this->_glfwWindow, WindowManager::_s_onWindowFocus);

        // Window Iconify
        glfwSetWindowIconifyCallback(this->_glfwWindow, WindowManager::_s_onWindowIconify);

        // Window Maximize
        glfwSetWindowMaximizeCallback(this->_glfwWindow, WindowManager::_s_onWindowMaximize);

        // Key
        glfwSetKeyCallback(this->_glfwWindow, WindowManager::_s_onKey);

        // Char
        glfwSetCharCallback(this->_glfwWindow, WindowManager::_s_onChar);

        // Char Mods
        glfwSetCharModsCallback(this->_glfwWindow, WindowManager::_s_onCharMods);

        // Mouse Button
        glfwSetMouseButtonCallback(this->_glfwWindow, WindowManager::_s_onMouseButton);

        // Cursor Position
        glfwSetCursorPosCallback(this->_glfwWindow, WindowManager::_s_onCursorPos);

        // Cursor Enter
        glfwSetCursorEnterCallback(this->_glfwWindow, WindowManager::_s_onCursorEnter);

        // Scroll
        glfwSetScrollCallback(this->_glfwWindow, WindowManager::_s_onScroll);

        // Drop
        glfwSetDropCallback(this->_glfwWindow, WindowManager::_s_onDrop);

        return true;
    }
}





// namespace DebugForIdeas {

//     int peekEvent();
//     int dispatchEvent();

//     void engine_update()
//     {
//         int event = peekEvent();
//         while (event) {
//             event = peekEvent();

//         }



//     }

//     void object_update()    // for user to do
//     {
//         // just handle single event for one frame
//         int single_event_per_frame = peekEvent();
//         switch (single_event_per_frame) {
//         case 0:
//         case 1:
//         default:
//             break;
//         }
//     }


// }