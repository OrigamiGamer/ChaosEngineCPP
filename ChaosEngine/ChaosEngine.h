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
    };

    template<typename T>
    struct vec3 {
        T x;
        T y;
        T z;
    };

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
    std::wstring getProgramFilePath();

    // Get the directory of the current running program.
    // 获取当前运行程序的目录。
    inline std::wstring getProgramFileDirectory();

    // Get the file name of the current running program.
    // 获取当前运行程序的文件名称。
    inline std::wstring getProgramFileName();

    // Format a file path.
    // 格式化文件路径。
    inline std::string formatFilePath(std::string filePath);
    inline std::wstring formatFilePath(std::wstring filePath);

    // Convert its relative path to absolute path.
    // 转换相对路径为绝对路径。
    std::wstring locate(std::wstring filename);

    // Get the directory of a file.
    // 获取文件的目录。
    std::string getFileDirectory(std::string filePath);
    std::wstring getFileDirectory(std::wstring filePath);

    // Get the name of a file.
    // 获取文件的名称。
    std::string getFileName(std::string filePath);
    std::wstring getFileName(std::wstring filePath);

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

    class Resource;

}



namespace Chaos::WindowX {

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

    using RenderTaskParam = std::variant<
        std::monostate,
        RenderTaskParam_Line,
        RenderTaskParam_Texture
    >;

    struct RenderTask;

    class Renderer;

}



namespace Chaos::Audio {

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
        InternalDevice::Engine* engine = nullptr;

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



    class Resource : public Base {
    public:
        Resource();
        ~Resource();

    };



}



#include "AudioX/AudioX.h"

#include "WindowX/WindowX.h"

#include "GraphicX/GraphicX.h"

#include "InternalDevice/InternalDevice.h"

#include "GameObject/GameObject.h"
