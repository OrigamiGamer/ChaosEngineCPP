#pragma once

#include "ChaosEngine.h"

namespace Chaos::WindowX {



    struct WindowProperty {
        Chaos::vec2<int> size = { 800, 600 };
        Chaos::vec2<int> pos = { -1, -1 };  // default position: center of screen
        std::string title = "Window";
    public:
        WindowProperty();
        WindowProperty(Chaos::vec2<int> size = { 800, 600 }, Chaos::vec2<int> pos = { -1, -1 }, std::string title = "Window");
    };



    class Window : public Base {
    public:
        GLFWwindow* _glfwWindow = nullptr;

        vec2<int> pos;  // value updated by callback
        vec2<int> size; // value updated by callback

        Window(InternalDevice::Engine* new_engine);
        ~Window();

        bool initialize(WindowProperty* new_windowProp = nullptr);

    };



    class WindowManager : public Base {
    public:
        static std::vector<WindowX::Window*> s_windows;

        WindowManager();

        static void _s_onWindowSize(GLFWwindow* window, int width, int height);
        static void _s_onWindowPos(GLFWwindow* window, int xpos, int ypos);
        static void _s_onWindowClose(GLFWwindow* window);
        static void _s_onWindowIconify(GLFWwindow* window, int iconified);
        static void _s_onWindowMaximize(GLFWwindow* window, int maximized);
        static void _s_onWindowFocus(GLFWwindow* window, int focused);
        static void _s_onKey(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void _s_onChar(GLFWwindow* window, unsigned int codepoint);
        static void _s_onCharMods(GLFWwindow* window, unsigned int codepoint, int mods);
        static void _s_onMouseButton(GLFWwindow* window, int button, int action, int mods);
        static void _s_onCursorPos(GLFWwindow* window, double xpos, double ypos);
        static void _s_onCursorEnter(GLFWwindow* window, int entered);
        static void _s_onScroll(GLFWwindow* window, double xoffset, double yoffset);
        static void _s_onDrop(GLFWwindow* window, int count, const char** paths);

        /*
            Window 'Window' key event - Key: 90, Scancode: 44, Action: 1, Mods: 0   (Key Down)
            Window 'Window' character with mods input - Codepoint: 122, Mods: 0
            Window 'Window' character input - Codepoint: 122                        (Char)
            Window 'Window' key event - Key: 90, Scancode: 44, Action: 0, Mods: 0   (Key Up)
        */

        static void registerWindow(WindowX::Window* window);
        static void registerWindow(WindowX::Window& window);

    };



}