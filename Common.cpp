#include <iostream>
#include <string>
#include <vector>
#include <chrono>

namespace Chaos {
    template<typename T>
    class safe_ptr {
    private:
        T* p = nullptr;
    public:
        ~safe_ptr()
        {
            release();
        }

        void set(T* p_new_value)
        {
            release();
            p = p_new_value;
        }

        bool has_value()
        {
            return p != nullptr;
        }

        T* get()
        {
            if (!has_value()) {
                // logger output: Unexpectation.Nullptr
            }
            return p;
        }

        void release()
        {
            if (has_value()) delete p;
            p = nullptr;
        }

        void operator=(safe_ptr new_ptr)
        {
            set(new_ptr.p);
        }

        void operator=(T* new_value)
        {
            set(new_value);
        }

        T* operator->()
        {
            if (p == nullptr) throw std::runtime_error("Unexpectation.Nullptr");
            return p;
        }
    };
}


// Common

// declarations
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
namespace Chaos::Device {
    class Engine {
    public:
        safe_ptr<Graphic::Renderer> renderer;
        safe_ptr<Device::Window> window;
        safe_ptr<Content::Stage> stage;

        Engine();
        void createRenderer(safe_ptr<Graphic::Renderer>* out_renderer);
        bool release();
    };

    class Window {
    public:
        safe_ptr<Device::Engine> engine;

        Window();
        ~Window();
    };
}

namespace Chaos::Graphic {
    class GraphicManager;
    class Renderer {
    public:
        safe_ptr<Device::Engine> engine;

        Renderer();
        ~Renderer();
    };
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


// Src
namespace Chaos {
    // Graphic::Renderer
    Graphic::Renderer::Renderer()
    {
        engine = nullptr;
    }

    Graphic::Renderer::~Renderer()
    {
        // release graphic api
    }

    // Device::Engine
    Device::Engine::Engine()
    {
        this->stage = nullptr;
        this->window = nullptr;
        this->renderer = nullptr;
    }

    void Device::Engine::createRenderer(safe_ptr<Graphic::Renderer>* out_renderer)
    {
        if (out_renderer != nullptr) renderer = new Graphic::Renderer();
    }

    bool Device::Engine::release()
    {
        renderer.release();
    }

}