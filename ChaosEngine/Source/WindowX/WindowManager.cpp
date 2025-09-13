#pragma once

#include "Class/WindowX/WindowX.h"

namespace Chaos::WindowX {



    std::vector<WindowX::Window*> WindowManager::s_windows;



    WindowManager::WindowManager()
    {
        this->INIT("WindowManager");
    }



    inline void WindowManager::registerWindow(WindowX::Window* window)
    {
        if (window) {
            for (auto& wnd : WindowManager::s_windows) if (wnd == window) return;   // avoid repetition
            WindowManager::s_windows.push_back(window);
        }
    }



    inline void WindowManager::registerWindow(WindowX::Window& window)
    {
        WindowManager::registerWindow(&window);
    }



    void WindowManager::_s_onWindowSize(GLFWwindow* window, int width, int height)
    {
        for (auto& wnd : WindowManager::s_windows) {
            if (wnd->_glfwWindow == window) {
                wnd->size = { width, height };
                wnd->_onResized();
                break;
            }
        }

        // const char* title = glfwGetWindowTitle(window);
        // std::cout << "Window '" << title << "' resized to width: " << width << ", height: " << height << std::endl;
    }



    void WindowManager::_s_onWindowPos(GLFWwindow* window, int xpos, int ypos)
    {
        for (auto& wnd : WindowManager::s_windows) {
            if (wnd->_glfwWindow == window) {
                wnd->pos = { xpos, ypos };
                break;
            }
        }

        // const char* title = glfwGetWindowTitle(window);
        // std::cout << "Window '" << title << "' moved to xpos: " << xpos << ", ypos: " << ypos << std::endl;
    }



    void WindowManager::_s_onWindowClose(GLFWwindow* window)
    {
        const char* title = glfwGetWindowTitle(window);
        std::cout << "Window '" << title << "' is about to close." << std::endl;
    }



    void WindowManager::_s_onWindowIconify(GLFWwindow* window, int iconified)
    {
        const char* title = glfwGetWindowTitle(window);
        if (iconified) {
            std::cout << "Window '" << title << "' has been iconified." << std::endl;
        }
        else {
            std::cout << "Window '" << title << "' has been restored." << std::endl;
        }
    }



    void WindowManager::_s_onWindowMaximize(GLFWwindow* window, int maximized)
    {
        const char* title = glfwGetWindowTitle(window);
        if (maximized) {
            std::cout << "Window '" << title << "' maximized." << std::endl;
        }
        else {
            std::cout << "Window '" << title << "' restored." << std::endl;
        }
    }



    void WindowManager::_s_onWindowFocus(GLFWwindow* window, int focused)
    {
        const char* title = glfwGetWindowTitle(window);
        if (focused) {
            std::cout << "Window '" << title << "' gained focus." << std::endl;
        }
        else {
            std::cout << "Window '" << title << "' lost focus." << std::endl;
        }
    }



    void WindowManager::_s_onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        for (auto& wnd : WindowManager::s_windows) {
            if (wnd->_glfwWindow == window) {
                // range from 0 to 348, and 349 virutal keys in total
                wnd->keyStateBuffer._keyStates.at(key).pressed = static_cast<bool>(action);
                wnd->keyStateBuffer._keyStates.at(key).released = !static_cast<bool>(action);
                wnd->_onKey(key);
                break;
            }
        }

        // const char* title = glfwGetWindowTitle(window);
        // std::cout << "Window '" << title << "' key event - Key: " << key << ", Scancode: " << scancode << ", Action: " << action << ", Mods: " << mods << std::endl;
    }



    void WindowManager::_s_onChar(GLFWwindow* window, unsigned int codepoint)
    {
        // const char* title = glfwGetWindowTitle(window);
        // std::cout << "Window '" << title << "' character input - Codepoint: " << codepoint << std::endl;
    }



    void WindowManager::_s_onCharMods(GLFWwindow* window, unsigned int codepoint, int mods)
    {
        // const char* title = glfwGetWindowTitle(window);
        // std::cout << "Window '" << title << "' character with mods input - Codepoint: " << codepoint << ", Mods: " << mods << std::endl;
    }



    void WindowManager::_s_onMouseButton(GLFWwindow* window, int button, int action, int mods)
    {
        // KeyStateBuffer
        // const char* title = glfwGetWindowTitle(window);
        // std::cout << "Window '" << title << "' mouse button ev/ent - Button: " << button << ", Action: " << action << ", Mods: " << mods << std::endl;
    }



    void WindowManager::_s_onCursorPos(GLFWwindow* window, double xpos, double ypos)
    {
        for (auto& wnd : WindowManager::s_windows) {
            if (wnd->_glfwWindow == window) {
                wnd->cursorPos.x = xpos;
                wnd->cursorPos.y = ypos;
                break;
            }
        }

        // const char* title = glfwGetWindowTitle(window);
        // std::cout << "Window '" << title << "' cursor position - Xpos: " << xpos << ", Ypos: " << ypos << std::endl;
    }



    void WindowManager::_s_onCursorEnter(GLFWwindow* window, int entered)
    {
        const char* title = glfwGetWindowTitle(window);
        if (entered) {
            std::cout << "Cursor entered the window '" << title << "'." << std::endl;
        }
        else {
            std::cout << "Cursor left the window '" << title << "'." << std::endl;
        }
    }



    void WindowManager::_s_onScroll(GLFWwindow* window, double xoffset, double yoffset)
    {
        const char* title = glfwGetWindowTitle(window);
        std::cout << "Window '" << title << "' scroll event - Xoffset: " << xoffset << ", Yoffset: " << yoffset << std::endl;
    }



    void WindowManager::_s_onDrop(GLFWwindow* window, int count, const char** paths)
    {
        const char* title = glfwGetWindowTitle(window);
        std::cout << "Window '" << title << "' files dropped in window - Count: " << count << std::endl;
        for (int i = 0; i < count; i++) {
            std::cout << "Window '" << title << "' path " << i << ": " << paths[i] << std::endl;
        }
    }



}