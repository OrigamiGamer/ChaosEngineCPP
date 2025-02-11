#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <memory>

#include "GLFW/glfw3.h"


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
        if (shared_ptr<T>::has_value()) this->release();
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
namespace Chaos {
    class Base;

    class Resource;
}

namespace Chaos::Device {
    class Engine;

    struct WindowProperty;

    class Window;
}

namespace Chaos::Graphic {
    class GraphicManager;

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
    class Engine : public Base {
    public:
        Chaos::ptr<Graphic::Renderer> renderer;
        Chaos::ptr<Device::Window> window;
        Chaos::ptr<Content::Stage> stage;

        Engine();
        ~Engine();

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

        // Initialize the engine in default configurations. Before every action of this engine, this method must be called.
        // 以默认配置初始化引擎。在该引擎执行任何行为之前，该方法必须被调用。
        bool initialize();

        // Only create the necessary devices for this engine in default configurations.
        // 仅为该引擎创建必需的设备，并以默认配置初始化它们。
        bool createDefaultDevice();

        // Bind a new Window device to this engine.
        // void bindWindow(Device::Window*);

        void start();

        void stop();

        // Proactively release all devices bound to the engine in a specific order.
        // 以特定顺序，主动释放引擎所拥有的所有设备。
        void release();
    };

    struct WindowProperty {
        Chaos::vec2<int> size;
        Chaos::vec2<int> pos;
        std::string title = "Window";
    };

    class Window : public Base {
    public:
        GLFWwindow* _glfwWindow;

        Window(Device::Engine* new_engine);
        ~Window();

        // Initialize a window object from a window property, or the default window property if parameter is empty. 
        // This method will return `true` for success.
        // 通过窗口配置来初始化一个窗口对象。若参数为空，则使用默认窗口配置。
        // 在成功时，该方法将返回 `true` 。
        bool initialize(WindowProperty* new_windowProp = nullptr);
    };
}

namespace Chaos::Graphic {
    class GraphicManager : public Base {
    public:
        GraphicManager(Device::Engine* new_engine);
        ~GraphicManager();
    };

    class Renderer : public Base {
    public:
        Renderer(Device::Engine* new_engine);
        ~Renderer();
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
