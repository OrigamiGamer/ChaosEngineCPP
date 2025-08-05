#pragma once

#include "ChaosEngine.h"

namespace Chaos::WindowX {



    class WindowManager : public Base {
    public:
        static std::vector<WindowX::Window*> s_windows;

        WindowManager();

        static void registerWindow(WindowX::Window* window);
        static void registerWindow(WindowX::Window& window);

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

    };



    struct WindowProperty {
        vec2<int> size = { 800, 600 };

        // If the value of a coordinate is -1, the position will be the center of primary monitor in that single coordinate.
        // 如果一个坐标轴的数值为 -1，那么在该坐标轴上，窗口位置将为初始显示器的中心。
        vec2<int> pos = { -1, -1 };

        std::string title = "Window";
    };



    class Window : public Base {
    private:
        GLFWwindow* _glfwWindow = nullptr;

        void _onResized();

    public:
        InternalDevice::Stage* stage = nullptr;

        WindowProperty initialProperty;

        vec2<int> pos;          // updated by callback
        vec2<int> size;         // updated by callback
        vec2<double> cursorPos; // updated by callback
        std::vector<bool> keyStateBuffer;   // The state buffer of virtual keys. See enum VirtualKey as index of this buffer.

        Window();

        bool initialize(WindowProperty* new_windowProp = nullptr);
        bool initialize(WindowProperty& new_windowProp);

        void release();

        std::string getTitle();

        void setTitle(std::string new_title);

        void setSize(vec2<int> new_size);

        bool getKeyState(int virtualKey);

        friend class WindowX::WindowManager;
        friend class GraphicX::Renderer;
        friend class InternalDevice::Stage;
        friend class InternalDevice::Engine;
    };



}