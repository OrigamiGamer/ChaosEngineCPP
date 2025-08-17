#pragma once

#include "WindowX/WindowX.h"

namespace Chaos::WindowX {



    Window::Window()
    {
        this->INIT("Window");
    }



    bool Window::initialize(WindowProperty* new_windowProp)
    {
        if (new_windowProp != nullptr) {
            // user's window property
            this->initialProperty = *new_windowProp;

            this->_glfwWindow = glfwCreateWindow(
                new_windowProp->size.x,
                new_windowProp->size.y,
                new_windowProp->title.c_str(),
                nullptr,
                nullptr
            );
            if (!this->_glfwWindow) return false;

            // calculate center pos of window in its monitor
            if (const GLFWvidmode* _vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor())) {
                if (new_windowProp->pos.x == -1) new_windowProp->pos.x = _vidmode->width / 2 - new_windowProp->size.x / 2;
                if (new_windowProp->pos.y == -1) new_windowProp->pos.y = _vidmode->height / 2 - new_windowProp->size.y / 2;

                glfwSetWindowPos(
                    this->_glfwWindow,
                    new_windowProp->pos.x,
                    new_windowProp->pos.y
                );
            }
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



    bool Window::initialize(WindowProperty& new_windowProp)
    {
        return this->initialize(&new_windowProp);
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



    void Window::_onKey(int virtualKey)
    {
        if (!this->stage) return;

        auto& keyState = this->keyStateBuffer._keyStates.at(virtualKey);
        // hot-key is pressed
        if (keyState._last_pressed != keyState.pressed) {
            if (keyState.pressed) {
                if (this->stage->_currentScene) {
                    for (auto& hotkey : keyState.hotkeys) {
                        // override callback
                        this->stage->_currentScene->onHotkeyPressed(hotkey.virtualKey);
                        this->stage->_currentScene->onHotkeyPressed(hotkey.hotkeyName);
                        // internal callback
                        this->stage->_currentScene->InternalDevice::Scene::onHotkeyPressed(hotkey.virtualKey);
                        this->stage->_currentScene->InternalDevice::Scene::onHotkeyPressed(hotkey.hotkeyName);
                    }
                }
            }
            keyState._last_pressed = keyState.pressed;
        }
        // hot-key is released
        if (keyState._last_released != keyState.released) {
            if (keyState.released) {
                if (this->stage->_currentScene) {
                    for (auto& hotkey : keyState.hotkeys) {
                        // override callback
                        this->stage->_currentScene->onHotkeyReleased(hotkey.virtualKey);
                        this->stage->_currentScene->onHotkeyReleased(hotkey.hotkeyName);
                        // internal callback
                        this->stage->_currentScene->InternalDevice::Scene::onHotkeyReleased(hotkey.virtualKey);
                        this->stage->_currentScene->InternalDevice::Scene::onHotkeyReleased(hotkey.hotkeyName);
                    }
                }
            }
            keyState._last_released = keyState.released;
        }

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



    bool Window::registerKeyStateBuffer(KeyStateBuffer* new_keyStateBuffer)
    {
        if (!new_keyStateBuffer) return false;

        for (auto& keyStateBuffer : this->_keyStateBuffers) {
            if (keyStateBuffer == new_keyStateBuffer) return false; // this state buffer of keys has already existed.
        }

        new_keyStateBuffer->window = this;
        this->_keyStateBuffers.push_back(new_keyStateBuffer);
        return true;
    }



    bool Window::unregisterKeyStateBuffer(KeyStateBuffer* new_keyStateBuffer)
    {
        if (!new_keyStateBuffer) return false;

        for (auto it = this->_keyStateBuffers.begin();it != this->_keyStateBuffers.end();it++) {
            if (*it == new_keyStateBuffer) {
                this->_keyStateBuffers.erase(it);
                return true;
            }
        }
        return false;   // could NOT find this target
    }



    bool Window::unregisterKeyStateBuffer(std::string keyStateBufferName)
    {
        if (keyStateBufferName.empty() || keyStateBufferName == "") return false;

        for (auto it = this->_keyStateBuffers.begin();it != this->_keyStateBuffers.end();it++) {
            if ((*it)->name == keyStateBufferName) {
                this->_keyStateBuffers.erase(it);
                return true;
            }
        }
        return false;   // could NOT find this target
    }



}
