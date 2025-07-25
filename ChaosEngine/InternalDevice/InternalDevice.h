#pragma once

#include "ChaosEngine.h"

namespace Chaos::InternalDevice {



    struct EngineStartupProperty {
        unsigned int fps = 60;
        Callback_GameInit onGameInit = nullptr;
        Callback_GameExit onGameExit = nullptr;
    };



    class Engine : public Base {
    private:
        void engineUpdate();

    public:
        // CAN it support MULTIPLE window devices?
        std::shared_ptr<GraphicX::Renderer> renderer = nullptr;
        std::shared_ptr<WindowX::Window> window = nullptr;
        std::shared_ptr<InternalDevice::Stage> stage = nullptr;
        InternalDevice::EngineStartupProperty engineStartupProp;
        bool gameRunningState = false;
        unsigned long long lastEngineTime = 0;
        unsigned long long deltaEngineTime = 0;

        Engine();

        bool initialize();

        void start(EngineStartupProperty* new_engineStartupProp = nullptr);

        void start(
            unsigned int new_fps = 60,
            Callback_GameInit new_onGameInit = nullptr,
            Callback_GameExit new_onGameExit = nullptr
        );

        void stop();

        void release();

        bool createWindow(WindowX::WindowProperty* new_windowProp = nullptr, std::shared_ptr<WindowX::Window>* out_window = nullptr);

        bool createRenderer(std::shared_ptr<GraphicX::Renderer>* out_renderer = nullptr);

        bool createStage(std::shared_ptr<InternalDevice::Stage>* out_stage = nullptr);

        bool createDefaultDevice();

    };



    class Stage : public Base {
    private:
        Chaos::WindowX::Window* _window = nullptr;
        std::vector<Scene*> _scenes;
        Scene* _currentScene = nullptr;
        Scene* _preparedScene = nullptr;
    public:
        Stage(InternalDevice::Engine* new_engine);

        void registerScene(Scene* new_scene);
        void registerScene(Scene& new_scene);

        void update();

        bool switchScene(std::string new_sceneName);
        void switchScene(Scene* new_scene);
        void switchScene(Scene& new_scene);

        friend class InternalDevice::Engine;
    };



    class Scene : public Base {
    public:
        Scene(std::string new_sceneName);

        virtual void update();

        virtual void onEntering();

        virtual bool onExiting();

    };



}
