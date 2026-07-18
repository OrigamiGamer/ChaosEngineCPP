#include "chaos/windows/windows.h"

namespace chaos::windows {



    Window::Window()
    {
        this->INIT("Window");
    }



    bool Window::initialize(WindowStartupProperty* in_windowProp)
    {
        if (in_windowProp != nullptr) {
            // user's window property
            this->startupProperty = *in_windowProp;

            this->_glfwWindow = glfwCreateWindow(
                in_windowProp->size.x,
                in_windowProp->size.y,
                in_windowProp->title.c_str(),
                nullptr,
                nullptr
            );
            if (!this->_glfwWindow) return false;

            // calculate center pos of window in its monitor
            if (const GLFWvidmode* _vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor())) {
                if (in_windowProp->position.x == -1) in_windowProp->position.x = _vidmode->width / 2 - in_windowProp->size.x / 2;
                if (in_windowProp->position.y == -1) in_windowProp->position.y = _vidmode->height / 2 - in_windowProp->size.y / 2;

                glfwSetWindowPos(
                    this->_glfwWindow,
                    in_windowProp->position.x,
                    in_windowProp->position.y
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



    inline bool Window::initialize(WindowStartupProperty& in_windowProp)
    {
        return this->initialize(&in_windowProp);
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



    void Window::_onKey(int keycode)
    {
        if (!this->stage) return;

        auto& keyState = this->keyStateBuffer._keyStates.at(keycode);
        // hot-key is pressed
        if (keyState._last_pressed != keyState.pressed) {
            if (keyState.pressed) {
                if (this->stage->_currentScene) {
                    for (auto& hotkey : keyState.hotkeys) {
                        // override callback
                        this->stage->_currentScene->onHotkeyPressed(hotkey.keycode);
                        this->stage->_currentScene->onHotkeyPressed(hotkey.hotkeyName);
                        // internal callback
                        this->stage->_currentScene->device::Scene::onHotkeyPressed(hotkey.keycode);
                        this->stage->_currentScene->device::Scene::onHotkeyPressed(hotkey.hotkeyName);
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
                        this->stage->_currentScene->onHotkeyReleased(hotkey.keycode);
                        this->stage->_currentScene->onHotkeyReleased(hotkey.hotkeyName);
                        // internal callback
                        this->stage->_currentScene->device::Scene::onHotkeyReleased(hotkey.keycode);
                        this->stage->_currentScene->device::Scene::onHotkeyReleased(hotkey.hotkeyName);
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



    void Window::setTitle(std::string in_title)
    {
        glfwSetWindowTitle(this->_glfwWindow, in_title.c_str());
    }



    void Window::setSize(vec2<int> in_size)
    {
        glfwSetWindowSize(this->_glfwWindow, in_size.x, in_size.y);
    }



    bool Window::registerKeyStateBuffer(KeyStateBuffer* in_keyStateBuffer)
    {
        if (!in_keyStateBuffer) return false;

        for (auto& keyStateBuffer : this->_keyStateBuffers) {
            if (keyStateBuffer == in_keyStateBuffer) return false; // This state buffer of keys has already existed.
        }

        in_keyStateBuffer->window = this;
        this->_keyStateBuffers.push_back(in_keyStateBuffer);
        return true;
    }



    bool Window::unregisterKeyStateBuffer(KeyStateBuffer* in_keyStateBuffer)
    {
        if (!in_keyStateBuffer) return false;

        for (auto it = this->_keyStateBuffers.begin();it != this->_keyStateBuffers.end();it++) {
            if (*it == in_keyStateBuffer) {
                this->_keyStateBuffers.erase(it);
                return true;
            }
        }
        return false;   // cannot find this target
    }



    bool Window::unregisterKeyStateBuffer(std::string keyStateBufferName)
    {
        if (keyStateBufferName.empty()) return false;

        for (auto it = this->_keyStateBuffers.begin();it != this->_keyStateBuffers.end();it++) {
            if ((*it)->nameId == keyStateBufferName) {
                this->_keyStateBuffers.erase(it);
                return true;
            }
        }
        return false;   // cannot find this target
    }



}
