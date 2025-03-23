#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <memory>

// GLFW
#define GLFW_EXPOSE_NATIVE_WIN32

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"


// DirectX
#include "Graphic/D2D/D2D.h"


namespace Chaos {

    // 1st-declarations
    template<typename T>
    struct vec2;

    template<typename T>
    struct vec3;

    template<typename T>
    class shared_ptr;

    template<typename T>
    class ptr;



    // 2nd-declarations
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

    template<typename T>
    class shared_ptr {
    private:
        T* p;
    public:
        shared_ptr();
        ~shared_ptr();

        bool has_value();

        T* operator->();

        // Refer a new pointer.
        // 引用一个新指针。
        shared_ptr<T>& refer(T* new_p);

        friend class ptr<T>;
    };

    template<typename T>
    class ptr : public shared_ptr<T> {
    public:
        ~ptr();

        void release();

        // Release and set a new pointer.
        // 释放旧指针内存，并设置一个新指针。
        ptr<T>& set(T* new_p);

        void operator=(T* new_p);
    };



    // Definitions
    template<typename T>
    shared_ptr<T>::shared_ptr()
    {
        p = nullptr;
    }

    template<typename T>
    shared_ptr<T>::~shared_ptr()
    {
        // std::cout << "do_nothing -> " << std::string(typeid(*this).name()) << std::endl;
    }

    template<typename T>
    inline bool shared_ptr<T>::has_value()
    {
        return p != nullptr;
    }

    template<typename T>
    inline T* shared_ptr<T>::operator->()
    {
        if (has_value()) return p;
        return nullptr;
    }

    template<typename T>
    shared_ptr<T>& shared_ptr<T>::refer(T* new_p)
    {
        this->p = new_p;
        return *this;
    }


    template<typename T>
    ptr<T>::~ptr()
    {
        // this->release();
    }

    template<typename T>
    inline void ptr<T>::release()
    {
        if (shared_ptr<T>::has_value()) delete shared_ptr<T>::p;
    }

    template<typename T>
    inline ptr<T>& ptr<T>::set(T* new_p)
    {
        if (shared_ptr<T>::has_value()) this->release();    // better to do nothing ?
        shared_ptr<T>::p = new_p;
        return *this;
    }

    template<typename T>
    inline void ptr<T>::operator=(T* new_ptr)
    {
        this->set(new_ptr);
    }
}



// Common

// 1st-declarations

namespace Chaos::System {

    template<typename T>
    void safeReleaseCOM(T*& pAny);

    template<typename T = IUnknown>
    void safeReleaseCOM(T*& pAny)
    {
        if (pAny != nullptr) {
            pAny->Release();
            pAny = nullptr;
        }
    }

    inline unsigned long long getSystemTime()
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
        ).count();
    }

    inline std::wstring getProgramPath()
    {
        wchar_t _raw_path[MAX_PATH]; GetModuleFileNameW(NULL, _raw_path, MAX_PATH);
        return std::wstring(_raw_path);
    }

    std::wstring locate(std::wstring fileName)
    {
        std::wstring raw = getProgramPath();

        size_t lpos = raw.find_last_of('\\');
        size_t rpos = raw.find_last_of('e');  //  \folder\test.exe
        size_t _rpos = raw.size() - 1;

        std::wstring root;
        if (rpos + 1 == raw.size()) {
            root = raw.substr(0, lpos + 1);
        }
        else {
            root = raw + L"\\";
        }
        return std::wstring(root) + fileName;
    }

    std::string codepointToUtf8(uint32_t codepoint)
    {
        std::wstring wideCharString;
        wideCharString.push_back(static_cast<wchar_t>(codepoint));

        int utf8Length = WideCharToMultiByte(CP_UTF8, 0, wideCharString.c_str(), -1, NULL, 0, NULL, NULL);
        if (utf8Length == 0) {
            return "";
        }

        std::vector<char> utf8String(utf8Length);
        WideCharToMultiByte(CP_UTF8, 0, wideCharString.c_str(), -1, utf8String.data(), utf8Length, NULL, NULL);
        utf8String.pop_back(); // remove char NULL

        return std::string(utf8String.begin(), utf8String.end());
    }

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
        std::string nameId;
        std::vector<std::string> typeIdHeap;
        Chaos::shared_ptr<Device::Engine> engine;
    public:
        Base();
        ~Base();

        void INIT(std::string new_typeId);

        void SET_NAME(std::string new_nameId);

        const size_t GET_TYPE_DEPTH();

        const std::string GET_TOP_TYPE();

        // Get the Global Unique Identifier(GUID) of this object.
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
        Chaos::ptr<Graphic::Renderer> renderer;
        Chaos::ptr<Device::Window> window;
        Chaos::ptr<Content::Stage> stage;
        EngineStartupProperty engineStartupProp;
        bool gameRunningState = false;
        unsigned long long lastEngineTime = 0;
        unsigned long long deltaEngineTime = 0;


        Engine();
        ~Engine();

        // Initialize this engine. Before every action of this engine, this method must be called.
        // 初始化引擎。在该引擎执行任何行为之前，该方法必须被调用。
        bool initialize();

        // Start this engine from a startup property, or the default property if parameter is nullptr.
        // 从指定配置启动引擎，若参数为空，则使用默认配置。
        void start(EngineStartupProperty* new_engineStartupProp = nullptr);

        void stop();

        // Proactively release all devices bound to the engine in a specific order.
        // 以特定顺序，主动释放引擎所拥有的所有设备。
        void release();

        // If this engine is not managing any Renderer device, it will create a new Renderer device bound to this engine, 
        // output its pointer into the optional parameter, and return `true` for success.
        // Else, this method will do nothing.
        // 若未拥有任何 Renderer 设备，引擎将创建一个新的 Renderer 设备，绑定到该引擎，输出其指针到参数，并在成功时返回 `true` 。
        // 否则该方法将不进行任何操作。
        bool createRenderer(Chaos::shared_ptr<Graphic::Renderer>* out_renderer = nullptr);

        // If this engine is not managing any Window device, it will create a new Window device bound to this engine, 
        // output its pointer into the optional parameter, and return `true` for success.
        // Initialize a window object from a window property, or the default window property if parameter is empty.
        // Else, this method will do nothing.
        // 若未拥有任何 Window 设备，引擎将创建一个新的 Window 设备，绑定到该引擎，输出其指针到参数，并在成功时返回 `true` 。
        // 通过窗口配置来初始化一个窗口对象。若参数为空，则使用默认窗口配置。
        // 否则该方法将不进行任何操作。
        bool createWindow(Device::WindowProperty* new_windowProp = nullptr, Chaos::shared_ptr<Device::Window>* out_window = nullptr);

        // If this engine is not managing any Stage device, it will create a new Stage device bound to this engine, 
        // output its pointer into the optional parameter, and return `true` for success. 
        // Else, this method will do nothing.
        // 若未拥有任何 Stage 设备，引擎将创建一个新的 Stage 设备，绑定到该引擎，输出其指针到参数，并在成功时返回 `true` 。
        // 否则该方法将不进行任何操作。
        bool createStage(Chaos::shared_ptr<Content::Stage>* out_stage = nullptr);

        // Only create the necessary devices for this engine in default configurations.
        // 仅为该引擎创建必需的设备，并以默认配置初始化它们。
        bool createDefaultDevice();

        // Bind a new Window device to this engine.
        // void bindWindow(Device::Window*);

    };

    struct WindowProperty {
        Chaos::vec2<int> size;
        Chaos::vec2<int> pos;
        std::string title = "Window";
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

    };

    class Texture : public Resource {
    public:
        ID2D1Bitmap* bitmap = nullptr;

        Texture();
        ~Texture();

        vec2<float> getSize();

    };

    class Renderer : public Base {
    private:
        ID2D1Factory* _d2dFactory = nullptr;
        IWICImagingFactory* _wicFactory = nullptr;
        IDWriteFactory* _dwriteFactory = nullptr;
        ID2D1HwndRenderTarget* _renderTarget = nullptr;
        ID2D1SolidColorBrush* _brush = nullptr;

    public:
        std::vector<Texture*> textures;

        Renderer(Device::Engine* new_engine);
        ~Renderer();

        bool initialize(Device::Window& new_window);

        Graphic::Texture* loadTextureFromFile(std::wstring filename);

        void drawLine(
            vec2<float> pos1,
            vec2<float> pos2,
            float strokeWidth = 1.0
        );

        void drawRectangle(vec2<float> pos, vec2<float> size);
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
    public:
        Stage(Device::Engine* new_engine);
        ~Stage();
    };

    class Scene : public Base {
    public:
        Scene(Device::Engine* new_engine);
        ~Scene();
    };

    class Actor : public Base {
    public:
        Actor(Device::Engine* new_engine);
        ~Actor();
    };

}
