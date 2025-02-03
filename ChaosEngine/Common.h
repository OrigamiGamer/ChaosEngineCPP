#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <memory>

namespace Chaos {
    template <typename T>
    class ptr;

    template <typename T>
    class ptr {
    private:
        T* p;
    public:
        ptr();
        ~ptr();

        bool has_value();

        T* operator->();

        void release();

        // Release and set a new pointer.
        // 释放旧指针的内存，并设置一个新指针
        void set(T* new_p);

        void operator=(T* new_p);
    };

    template<typename T>
    ptr<T>::ptr()
    {
        p = nullptr;
    }

    template<typename T>
    ptr<T>::~ptr()
    {
        delete p;
    }

    template<typename T>
    inline bool ptr<T>::has_value()
    {
        return p != nullptr;
    }

    template<typename T>
    inline T* ptr<T>::operator->()
    {
        if (has_value()) return p;

    }

    template<typename T>
    inline void ptr<T>::release()
    {
        if (has_value()) delete p;
    }

    template<typename T>
    inline void ptr<T>::set(T* new_p)
    {
        if (has_value()) release();
        p = new_p;
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
        std::wstring nameId;
        std::wstring uniqueId;  // also UID
        Chaos::ptr<Device::Engine> engine;

        Base();
        ~Base();
    };

    class Resource : Base {
    public:
        Resource();
        ~Resource();
    };
}

namespace Chaos::Device {
    class Engine : Base {
    public:
        Chaos::ptr<Graphic::Renderer> renderer;
        Chaos::ptr<Device::Window> window;
        Chaos::ptr<Content::Stage> stage;

        Engine();
        ~Engine();

        // If the engine is not managing any Renderer device, it will create a new Renderer device bound to the engine itself, output its pointer into parameter, and return true for success.
        // 若未拥有任何 Renderer 设备，引擎将创建一个新的 Renderer 设备，绑定到引擎自身，输出其指针到参数，并返回 true 。
        bool createRenderer(Chaos::ptr<Graphic::Renderer>* out_renderer = nullptr);

        // If the engine is not managing any Window device, it will create a new Window device bound to the engine itself, output its pointer into parameter, and return true for success.
        // 若未拥有任何 Window 设备，引擎将创建一个新的 Window 设备，绑定到引擎自身，输出其指针到参数，并返回 true 。
        bool createWindow(Chaos::ptr<Device::Window>* out_window = nullptr);

        void release();
    };

    class Window : Base {
    public:
        Window(Device::Engine* new_engine);
        ~Window();
    };
}

namespace Chaos::Graphic {
    class GraphicManager : Base {
    public:
        GraphicManager(Device::Engine* new_engine);
        ~GraphicManager();
    };

    class Renderer : Base {
    public:
        Renderer(Device::Engine* new_engine);
        ~Renderer();
    };
}

namespace Chaos::Audio {
    class AudioManager : Base {
    public:
        AudioManager(Device::Engine* new_engine);
        ~AudioManager();
    };

    class Sound : Resource {
    public:
        Sound(Device::Engine* new_engine);
        ~Sound();
    };

    class Sample : Resource {
    public:
        Sample(Device::Engine* new_engine);
        ~Sample();
    };

    class Channel : Resource {
    public:
        Channel(Device::Engine* new_engine);
        ~Channel();
    };

    class ChannelGroup : Resource {
    public:
        ChannelGroup(Device::Engine* new_engine);
        ~ChannelGroup();
    };

    class AudioPlayer : Base {
    public:
        AudioPlayer(Device::Engine* new_engine);
        ~AudioPlayer();
    };
}

namespace Chaos::Content {
    class Stage : Base {
    public:
        Stage(Device::Engine* new_engine);
        ~Stage();
    };

    class Scene : Base {
    public:
        Scene(Device::Engine* new_engine);
        ~Scene();
    };

    class Actor : Base {
    public:
        Actor(Device::Engine* new_engine);
        ~Actor();
    };
}
