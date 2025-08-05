#pragma once

#include "WindowX/WindowX.h"

namespace Chaos::WindowX {



    Window::Window() :
        keyStateBuffer(349, false)
    {
        this->INIT("Window");
    }



    bool Window::initialize(WindowProperty* new_windowProp)
    {
        if (new_windowProp != nullptr) {
            // user's window property
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

            this->initialProperty = *new_windowProp;
        }
        else {
            // default window property
            this->_glfwWindow = glfwCreateWindow(
                1280,
                720,
                "Window",
                nullptr,
                nullptr
            );
            if (!this->_glfwWindow) return false;
        }
        glfwGetWindowPos(this->_glfwWindow, &this->pos.x, &this->pos.y);
        glfwGetWindowSize(this->_glfwWindow, &this->size.x, &this->size.y);

        // register the window created to WindowManager
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



    void Window::release()
    {
        if (this->_glfwWindow) glfwDestroyWindow(this->_glfwWindow);
    }



    void Window::_onResized()
    {
        if (this->stage && this->stage->engine && this->stage->engine->renderer)
            this->stage->engine->renderer->_resizeWindow(this->size);
    }



    std::string Window::getTitle()
    {
        return glfwGetWindowTitle(this->_glfwWindow);
    }



    void Window::setTitle(std::string new_title)
    {
        glfwSetWindowTitle(this->_glfwWindow, new_title.c_str());
    }



    void Window::setSize(vec2<int> new_size)
    {
        glfwSetWindowSize(this->_glfwWindow, new_size.x, new_size.y);
    }



    bool Window::getKeyState(int virtualKey)
    {
        if (virtualKey > 0 && virtualKey <= VirtualKey::LAST_VIRTUAL_KEY)
            return this->keyStateBuffer.at(virtualKey);
        return false;
    }



}
