#pragma once



// STL

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <memory>
#include <variant>
#include <algorithm>



// OpenAL

#include "ExternalLibrary/Audio/OpenAL/OpenAL.h"



// GLFW

#define GLFW_EXPOSE_NATIVE_WIN32

#include "ExternalLibrary/GLFW/glfw3.h"
#include "ExternalLibrary/GLFW/glfw3native.h"



// DirectX

#include "ExternalLibrary/Graphic/D2D/D2D.h"



// Common

// ----------------
// 1st-declarations
// ----------------

namespace Chaos {

    template<typename T>
    struct vec2 {
        T x;
        T y;
    public:
        vec2() {}
        vec2(T x, T y) : x(x), y(y) {}
        vec2<T> operator+(vec2<T>& other) { return { this->x + other.x, this->y + other.y }; }
        vec2<T> operator-(vec2<T>& other) { return { this->x - other.x, this->y - other.y }; }
        vec2<T> operator*(vec2<T>& other) { return { this->x * other.x, this->y * other.y }; }
        vec2<T> operator/(vec2<T>& other) { return { this->x / other.x, this->y / other.y }; }
        void operator+=(vec2<T>& other) { this.x += other.x; this.y += other.y; }
        void operator-=(vec2<T>& other) { this.x -= other.x; this.y -= other.y; }
        void operator*=(vec2<T>& other) { this.x *= other.x; this.y *= other.y; }
        void operator/=(vec2<T>& other) { this.x /= other.x; this.y /= other.y; }
    };

    template<typename T>
    struct vec3 {
        T x;
        T y;
        T z;
    public:
        vec3() {}
        vec3(T x, T y, T z) : x(x), y(y), z(z) {}
        vec3<T> operator+(vec3<T>& other) { return { this->x + other.x, this->y + other.y, this->z + other.z }; }
        vec3<T> operator-(vec3<T>& other) { return { this->x - other.x, this->y - other.y, this->z - other.z }; }
        vec3<T> operator*(vec3<T>& other) { return { this->x * other.x, this->y * other.y, this->z * other.z }; }
        vec3<T> operator/(vec3<T>& other) { return { this->x / other.x, this->y / other.y, this->z / other.z }; }
        void operator+=(vec3<T>& other) { this.x += other.x; this.y += other.y; this->z += other.z; }
        void operator-=(vec3<T>& other) { this.x -= other.x; this.y -= other.y; this->z -= other.z; }
        void operator*=(vec3<T>& other) { this.x *= other.x; this.y *= other.y; this->z *= other.z; }
        void operator/=(vec3<T>& other) { this.x /= other.x; this.y /= other.y; this->z /= other.z; }

    };

    // Force to transform type of vector from "float" to "int".
    // 强制转换向量类型从 单精度浮点型 到 整数型。
    inline vec2<int> vecf2i(vec2<float>& vecf);
    inline vec3<int> vecf2i(vec3<float>& vecf);

    // Force to transform type of vector from "int" to "float".
    // 强制转换向量类型从 整数型 到 单精度浮点型。
    inline vec2<float> veci2f(vec2<int>& vecf);
    inline vec3<float> veci2f(vec3<int>& vecf);


}



namespace Chaos::System {

    // Release a COM object pointer safely.
    // 安全释放 COM 对象指针。
    template<typename T>
    void safeReleaseCOM(T*& pAny);

    // Get the current system time in microseconds.
    // 获取当前系统时间，以微秒为单位。
    unsigned long long getSystemTime();

    // Get the path of the current running program.
    // 获取当前运行程序的路径。
    std::string getProgramFilePath();
    std::wstring getProgramFilePathW();

    // Get the directory of the current running program.
    // 获取当前运行程序的目录。
    inline std::string getProgramFileDirectory();
    inline std::wstring getProgramFileDirectoryW();

    // Get the file name of the current running program.
    // 获取当前运行程序的文件名称。
    inline std::string getProgramFileName();
    inline std::wstring getProgramFileNameW();

    // Format a file path.
    // 格式化文件路径。
    inline std::string formatFilePath(std::string filePath);
    inline std::wstring formatFilePathW(std::wstring filePath);

    // Convert its relative path to absolute path.
    // 转换相对路径为绝对路径。
    std::string locate(std::string filename);
    std::wstring locateW(std::wstring filename);

    // Get the directory of a file.
    // 获取文件的目录。
    std::string getFileDirectory(std::string filePath);
    std::wstring getFileDirectoryW(std::wstring filePath);

    // Get the name of a file.
    // 获取文件的名称。
    std::string getFileName(std::string filePath);
    std::wstring getFileNameW(std::wstring filePath);

    // Convert a Unicode codepoint to UTF-8 string.
    // 将 Unicode 代码点转换为 UTF-8 字符串。
    std::string codepointToUtf8(uint32_t codepoint);

    // Convert a Unicode string to UTF-8 string.
    // 将 Unicode 字符串转换为 UTF-8 字符串。
    std::string wstringToString(const std::wstring wstr);

    // Convert a UTF-8 string to Unicode string.
    // 将 UTF-8 字符串转换为 Unicode 字符串。
    std::wstring stringToWstring(const std::string str);

}



namespace Chaos {

    class Base;

    class Device;

    class Resource;

}



namespace Chaos::WindowX {

    namespace VirtualKey {
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
        const int LAST_VIRTUAL_KEY = VirtualKey::Menu;
    }

    struct WindowProperty;

    class Window;

    class WindowManager;

}



namespace Chaos::InternalDevice {

    typedef void (*Callback_GameInit)();

    typedef bool (*Callback_GameExit)();

    struct EngineStartupProperty;

    class Engine;

    class Stage;    // based on windows

    class Scene;    // the game world

}



namespace Chaos::GraphicX {

    class GraphicManager;

    class Texture;

    class Viewport;

    enum struct RenderTaskType {
        None,
        Line,
        Texture,
    };

    struct RenderTaskParam_Line;
    struct RenderTaskParam_Texture;

    // general type
    using RenderTaskParam = std::variant<
        std::monostate,
        RenderTaskParam_Line,
        RenderTaskParam_Texture
    >;

    struct RenderTask;

    class Renderer;

}



namespace Chaos::AudioX {

    class AudioManager;

    class Sound;

    class Sample;

    class Channel;

    class ChannelGroup;

    class AudioPlayer;

}



namespace Chaos::GameObject {

    class Actor;    // any placeable actor in scenes on stage

}



// ----------------
// 2nd-declarations
// ----------------

namespace Chaos {



    class Base {
    public:
        std::string name;
        std::vector<std::string> typeHeap;

        Base();

        ~Base();

        virtual void release();

        void INIT(std::string new_type);

        void SET_NAME(std::string new_name);

        // Get the depth of the type of this object
        // 获取该对象类型的深度。
        const size_t GET_TYPE_DEPTH();

        // Get the type name of this object.
        // 获取该对象顶层类型的名称。
        const std::string GET_TOP_TYPE();

        // Get the Global Unique Identifier(GUID) of this object.
        // 获取该对象的全局唯一标识符(GUID)。
        std::string GET_GUID();

    };



    class Device : public Base {
    public:
        InternalDevice::Engine* engine = nullptr;

        Device();

        ~Device();

    };



    class Resource : public Base {
    public:
        Resource();

    };



}



#include "AudioX/AudioX.h"

#include "WindowX/WindowX.h"

#include "GraphicX/GraphicX.h"

#include "InternalDevice/InternalDevice.h"

#include "GameObject/GameObject.h"
