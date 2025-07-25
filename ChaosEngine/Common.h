#pragma once

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

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"


// DirectX
#include "Graphic/D2D/D2D.h"



// Common

// 1st-declarations

namespace Chaos {

    template<typename T>
    struct vec2;

    template<typename T>
    struct vec3;

    // A shared pointer model, possessing a pointer's access but not managing it. (It looks like a observer...)
    // 共享指针模型，拥有指针的访问权限，但并不负责管理它。（它看起来像个观察者...）
    template<typename T>
    class shared_ptr;

    // A unique pointer model, managing a pointer as the unique owner. (A miser...)
    // 独占指针模型，指针唯一管理者。（吝啬鬼...）
    template<typename T>
    class ptr;



    // 2nd-declarations
    template<typename T>
    struct vec2 {
        T x;
        T y;
        vec2();
        vec2(T x, T y);
    };

    template<typename T>
    struct vec3 {
        T x;
        T y;
        T z;
        vec3();
        vec3(T x, T y, T z);
    };

    template<typename T>
    class shared_ptr {
    private:
        T* p = nullptr;
    public:
        shared_ptr(T* new_p = nullptr);
        ~shared_ptr();

        bool has_value();

        T* get();

        T* operator->();

        // Refer a new pointer.
        // 引用一个新指针。
        shared_ptr<T>& refer(T* new_p);

        shared_ptr<T>& refer(shared_ptr<T>& new_p);

        shared_ptr<T>& operator=(T* new_p);

        shared_ptr<T>& operator=(shared_ptr<T>& new_p);

        friend class ptr<T>;
    };

    template<typename T>
    class ptr : public shared_ptr<T> {
    public:
        ptr(T* new_p = nullptr);
        ~ptr();

        void release();

        // Release and set a new pointer.
        // 释放旧指针内存，并设置一个新指针。
        ptr<T>& set(T* new_p);

        void operator=(T* new_p);
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

namespace Chaos::Device {

    typedef void (*Callback_GameInit)();

    typedef bool (*Callback_GameExit)();

    struct EngineStartupProperty;

    class Engine;

    struct WindowProperty;

    class Window;

    class WindowManager;

}

namespace Chaos::Graphic {

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

namespace Chaos::Content {

    class Stage;

    class Scene;

    class Actor;

}


// 2nd-declarations
namespace Chaos {

    class Base {
    public:
        std::string name;
        std::vector<std::string> typeHeap;
        Chaos::shared_ptr<Device::Engine> engine;
    public:
        Base();
        ~Base();

        void INIT(std::string new_type);

        void SET_NAME(std::string new_name);

        // Get the type depth of this object.
        // 获取对象类型深度。
        const size_t GET_TYPE_DEPTH();

        // Get the type name of this object.
        // 获取对象顶层类型名称。
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

namespace Chaos::Device {

    struct EngineStartupProperty {
        unsigned int fps = 60;
        Callback_GameInit onGameInit = nullptr;
        Callback_GameExit onGameExit = nullptr;
    };

    class Engine : public Base {
    private:
        void engineUpdate();

    public:
        Chaos::ptr<Graphic::Renderer> renderer = nullptr;
        Chaos::ptr<Device::Window> window = nullptr;
        Chaos::ptr<Content::Stage> stage = nullptr;
        EngineStartupProperty engineStartupProp;
        bool gameRunningState = false;
        unsigned long long lastEngineTime = 0;
        unsigned long long deltaEngineTime = 0;


        Engine();
        ~Engine();

        // Initialize this engine. This method MUST be called before any action of this engine.
        // 初始化引擎。在该引擎执行任何行为之前，该方法必须被调用。
        bool initialize();

        // Start this engine from a startup property, or the default property if parameter is nullptr.
        // 从指定配置启动引擎，若参数为空，则使用默认配置。
        void start(EngineStartupProperty* new_engineStartupProp = nullptr);

        void start(
            unsigned int new_fps = 60,
            Callback_GameInit new_onGameInit = nullptr,
            Callback_GameExit new_onGameExit = nullptr
        );

        void stop();

        // Proactively release all devices bound to the engine in a specific order.
        // 以特定顺序，主动释放引擎所拥有的所有设备。
        void release();

        // If this engine is not managing any Window device, it will create a new Window device bound to this engine, 
        // output its pointer into the optional parameter, and return `true` for success.
        // Initialize a window object from a window property, or the default window property if parameter is empty.
        // Else, this method will do nothing.
        // 若未拥有任何 Window 设备，引擎将创建一个新的 Window 设备，绑定到该引擎，输出其指针到参数，并在成功时返回 `true` 。
        // 通过窗口配置来初始化一个窗口对象。若参数为空，则使用默认窗口配置。
        // 否则该方法将不进行任何操作。
        bool createWindow(Device::WindowProperty* new_windowProp = nullptr, Chaos::shared_ptr<Device::Window>* out_window = nullptr);

        // If this engine is not managing any Renderer device, it will create a new Renderer device bound to this engine, 
        // output its pointer into the optional parameter, and return `true` for success.
        // Else, this method will do nothing.
        // 若未拥有任何 Renderer 设备，引擎将创建一个新的 Renderer 设备，绑定到该引擎，输出其指针到参数，并在成功时返回 `true` 。
        // 否则该方法将不进行任何操作。
        bool createRenderer(Chaos::shared_ptr<Graphic::Renderer>* out_renderer = nullptr);

        // If this engine is not managing any Stage device, it will create a new Stage device bound to this engine, 
        // output its pointer into the optional parameter, and return `true` for success. 
        // Else, this method will do nothing.
        // 若未拥有任何 Stage 设备，引擎将创建一个新的 Stage 设备，绑定到该引擎，输出其指针到参数，并在成功时返回 `true` 。
        // 否则该方法将不进行任何操作。
        bool createStage(Chaos::shared_ptr<Content::Stage>* out_stage = nullptr);

        // Only create the necessary devices for this engine in default configurations.
        // 仅为该引擎创建必需的设备，并以默认配置初始化它们。
        bool createDefaultDevice();

        //// Bind a new Window device to this engine.
        // void bindWindow(Device::Window*);

    };

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

        Window(Device::Engine* new_engine);
        ~Window();

        // Initialize a window object from a window property, or the default window property if parameter is empty. 
        // This method will return `true` for success.
        // 通过窗口配置来初始化一个窗口对象。若参数为空，则使用默认窗口配置。
        // 在成功时，该方法将返回 `true` 。
        bool initialize(WindowProperty* new_windowProp = nullptr);

    };

    class WindowManager : public Base {
    public:
        static std::vector<Device::Window*> s_windows;

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

        static void registerWindow(Device::Window* window);
        static void registerWindow(Device::Window& window);

    };

}

namespace Chaos::Graphic {

    class GraphicManager : public Base {
    public:
        Chaos::shared_ptr<Graphic::Renderer> renderer;

        GraphicManager(Device::Engine* new_engine);
        ~GraphicManager();

        void registerRenderer(Graphic::Renderer* new_renderer);
        void registerRenderer(Graphic::Renderer& new_renderer);

    };

    class Bitmap {
    private:
        ID2D1Bitmap* _d2dbitmap = nullptr;

        vec2<float> getSize();

    public:
        Bitmap();
        ~Bitmap();

        friend class Texture;
        friend class Renderer;
    };

    class Texture : public Resource {
    private:
        Chaos::shared_ptr<Bitmap> _bitmap;

    public:
        Texture();
        ~Texture();

        vec2<float> getSize();

        friend class Renderer;
    };

    // Arguments of task types.
    // 任务类型的参数。

    // Line
    struct RenderTaskParam_Line {
        vec2<float> pos1{};
        vec2<float> pos2{};
        float strokeWidth = 1.0;

        RenderTaskParam_Line(
            vec2<float> pos1,
            vec2<float> pos2,
            float strokeWidth = 1.0
        );
    };

    struct RenderTaskParam_Texture {
        vec2<float> pos{};
        vec2<float> size{};
        Texture* texture = nullptr;
        float opacity = 1.0;
        vec2<float> pivot{};
        float rotation = 0.0;

        // If `size` is `-1`, it will use the texture's size.
        // 如果 `size` 为 `-1`，则使用纹理大小。
        RenderTaskParam_Texture(
            vec2<float> pos,
            Texture* texture,
            vec2<float> size = { -1,-1 },
            vec2<float> pivot = { 0.0,0.0 },
            float rotation = 0.0
        );
    };

    struct RenderTask {
        RenderTaskType type = RenderTaskType::None;
        RenderTaskParam param;
        float order = 0.0;
        RenderTask(RenderTaskType type = RenderTaskType::None, RenderTaskParam param = RenderTaskParam(), float order = 0.0);
    };

    class Viewport : public Base {
    private:
        Graphic::Bitmap _bitmap;
    public:
        Chaos::vec2<float> pos;
        Chaos::vec2<float> size;
        Chaos::vec2<float> pivot;
        float rotation;

        Chaos::vec2<float> viewPos;
        Chaos::vec2<float> viewSize;

        Viewport(Device::Engine* new_engine);
        ~Viewport();

        friend class Renderer;
    };

    class Renderer : public Base {
    private:
        ID2D1Factory* _d2dFactory = nullptr;
        IWICImagingFactory* _wicFactory = nullptr;
        IDWriteFactory* _dwriteFactory = nullptr;

        ID2D1HwndRenderTarget* _hwndRenderTarget = nullptr;

        ID2D1BitmapRenderTarget* _bitmapRenderTarget = nullptr;
        ID2D1SolidColorBrush* _brush = nullptr;

        std::vector<Bitmap> _loadedBitmaps;
        std::map<std::string, Texture> _loadedTextures;

    public:
        std::vector<RenderTask> tasks;
        // std::vector<Chaos::ptr<Graphic::Viewport>> viewports;
        std::vector<Graphic::Viewport> viewports;   // why do i use ptr?

        Renderer(Device::Engine* new_engine);
        ~Renderer();

        bool initialize(Device::Window* new_window);
        bool initialize(Device::Window& new_window);

        bool createViewport(std::string viewportName = "", Chaos::shared_ptr<Graphic::Viewport>* out_viewport = nullptr);
        bool createViewport(Chaos::shared_ptr<Graphic::Viewport>& out_viewport);

        Texture* loadTextureFromImageFile(std::wstring filename, std::string textureName = "");
        Texture* getLoadedTexture(std::string textureName);

        void pushTask(RenderTask& new_task);

        // Pop the last task from the task queue.
        void popTask();

        void beginDraw();

        void endDraw();

        friend class Content::Stage;
    };

}

namespace Chaos::Audio {

    class AudioManager : public Base {
    public:
        AudioManager(Device::Engine* new_engine);
        ~AudioManager();
    };

    class Sound : public Resource {
    public:
        Sound(Device::Engine* new_engine);
        ~Sound();
    };

    class Sample : public Resource {
    public:
        Sample(Device::Engine* new_engine);
        ~Sample();
    };

    class Channel : public Resource {
    public:
        Channel(Device::Engine* new_engine);
        ~Channel();
    };

    class ChannelGroup : public Resource {
    public:
        ChannelGroup(Device::Engine* new_engine);
        ~ChannelGroup();
    };

    class AudioPlayer : public Base {
    public:
        AudioPlayer(Device::Engine* new_engine);
        ~AudioPlayer();
    };

}

namespace Chaos::Content {

    class Stage : public Base {
    private:
        std::vector<Chaos::shared_ptr<Scene>> _scenes;
        Chaos::shared_ptr<Scene> _currentScene;
        Chaos::shared_ptr<Scene> _preparedScene;

    public:
        Stage(Device::Engine* new_engine);
        ~Stage();

        // Register a new scene to this stage. And the engine bound to the new scene will be rebound.
        // 注册一个新场景到该舞台，且该场景所属的引擎将被重新绑定。
        void registerScene(Scene* new_scene);
        void registerScene(Scene& new_scene);
        void registerScene(Chaos::shared_ptr<Scene>& new_scene);

        void update();

        bool switchScene(std::string new_sceneName);
        void switchScene(Scene* new_scene);
        void switchScene(Scene& new_scene);
        void switchScene(Chaos::shared_ptr<Scene>& new_scene);

        friend class Device::Engine;
    };

    class Scene : public Base {
    public:
        Scene(std::string new_sceneName);
        ~Scene();

        virtual void update();

        virtual void onEnter();

        virtual bool onExit();

    };

    class Actor : public Base {
    public:
        Actor(Device::Engine* new_engine);
        ~Actor();
    };

}
