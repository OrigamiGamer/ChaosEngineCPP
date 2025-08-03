#pragma once

#include "ChaosEngine.h"

namespace Chaos::WindowX {



    enum VirtualKey {
        Space = 32,
        Apostrophe = 39,    /* ' */
        Comma = 44,         /* , */
        Minus = 45,         /* - */
        Period = 46,        /* . */
        Slash = 47,         /* / */
        Number_0 = 48,
        Number_1 = 49,
        Number_2 = 50,
        Number_3 = 51,
        Number_4 = 52,
        Number_5 = 53,
        Number_6 = 54,
        Number_7 = 55,
        Number_8 = 56,
        Number_9 = 57,
        Semicolon = 59,     /* ; */
        Equal = 61,         /* = */
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,
        LeftBracket = 91,   /* [ */
        BackSlash = 92,     /* \ */
        RightBracket = 93,  /* ] */
        GraveAccent = 96,   /* ` */
        World_1 = 161,      /* non-US #1 */
        World_2 = 162,      /* non-US #2 */

        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,
        KP_0 = 320,
        KP_1 = 321,
        KP_2 = 322,
        KP_3 = 323,
        KP_4 = 324,
        KP_5 = 325,
        KP_6 = 326,
        KP_7 = 327,
        KP_8 = 328,
        KP_9 = 329,
        KP_Decimal = 330,
        KP_Divide = 331,
        KP_Multiply = 332,
        KP_Subtract = 333,
        KP_Add = 334,
        KP_Enter = 335,
        KP_Equal = 336,
        L_Shift = 340,
        L_Control = 341,
        L_Alt = 342,
        L_Super = 343,
        R_Shift = 344,
        R_Control = 345,
        R_Alt = 346,
        R_Super = 347,
        Menu = 348,
    };



    struct WindowProperty {
        Chaos::vec2<int> size = { 800, 600 };
        Chaos::vec2<int> pos = { -1, -1 };  // default position: center of screen
        std::string title = "Window";
    };



    class Window : public Base {
    private:
        GLFWwindow* _glfwWindow = nullptr;

    public:
        InternalDevice::Stage* stage = nullptr;

        WindowProperty initialProperty;

        vec2<int> pos;          // updated by callback
        vec2<int> size;         // updated by callback
        vec2<double> cursorPos; // updated by callback
        std::vector<bool> keyStateBuffer;   // virtual-key codes from 0x01 to 0xFE (size: 255)

        Window();

        bool initialize(WindowProperty* new_windowProp = nullptr);

        void release();

        std::string getTitle();

        void setTitle(std::string new_windowTitle);

        bool getKeyState(int virtualKey);

        friend class WindowX::WindowManager;
        friend class GraphicX::Renderer;
        friend class InternalDevice::Stage;
        friend class InternalDevice::Engine;
    };



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



}