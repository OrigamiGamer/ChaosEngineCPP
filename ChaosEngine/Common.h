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

        bool has_value();

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
    inline bool ptr<T>::has_value()
    {
        return p != nullptr;
    }

    template <typename T>
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

        // Having not been managing any device about Renderer, the engine will create a new Renderer device bound to itself, 
        // and return true for success.
        // 若未拥有任何 Renderer 有关设备，引擎将创建一个新的 Renderer 设备，绑定到引擎自身，并返回 true 。
        bool createRenderer(Chaos::ptr<Graphic::Renderer>* out_renderer);
        bool createRenderer();

        void release();
    };

    class Window : Base {
    public:
        std::unique_ptr<Device::Engine> engine;

        Window();
        ~Window();
    };
}

namespace Chaos::Graphic {
    class GraphicManager : Base {
    public:
        GraphicManager();
        ~GraphicManager();
    };

    class Renderer : Base {
    public:
        std::unique_ptr<Device::Engine> engine;

        Renderer();
        ~Renderer();
    };
}

namespace Chaos::Audio {
    class AudioManager : Base {
    public:
        AudioManager();
        ~AudioManager();
    };

    class Sound : Resource {
    public:
        Sound();
        ~Sound();
    };

    class Sample : Resource {
    public:
        Sample();
        ~Sample();
    };

    class Channel : Resource {
    public:
        Channel();
        ~Channel();
    };

    class ChannelGroup : Resource {
    public:
        ChannelGroup();
        ~ChannelGroup();
    };

    class AudioPlayer : Base {
    public:
        AudioPlayer();
        ~AudioPlayer();
    };
}

namespace Chaos::Content {
    class Stage : Base {
    public:
        Stage();
        ~Stage();
    };

    class Scene : Base {
    public:
        Scene();
        ~Scene();
    };

    class Actor : Base {
    public:
        Actor();
        ~Actor();
    };
}
