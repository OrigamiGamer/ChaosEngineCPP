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
        void windowUpdate();

        void engineUpdate();

    public:
        GraphicX::Renderer* renderer = nullptr;
        InternalDevice::Stage* stage = nullptr;

        InternalDevice::EngineStartupProperty engineStartupProp;
        bool gameRunningState = false;
        unsigned long long lastEngineTime = 0;  // units: microseconds
        unsigned long long deltaEngineTime = 0; // units: microseconds

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

        void registerRenderer(GraphicX::Renderer* new_renderer);

        void registerStage(InternalDevice::Stage* new_stage);

    };



    class Stage : public Device {
    private:
        std::vector<Scene*> _scenes;
        Scene* _currentScene = nullptr;
        Scene* _preparedScene = nullptr;

        void _updateWindow();

    public:
        std::vector<Chaos::WindowX::Window*> windows;

        Stage();

        void release();

        void registerWindow(WindowX::Window* new_window);
        void registerWindow(WindowX::Window& new_window);

        void unregisterWindow(std::string windowTitle, std::string windowName = "");

        void registerScene(Scene* new_scene);
        void registerScene(Scene& new_scene);

        void update();

        bool switchScene(std::string new_sceneName);
        void switchScene(Scene* new_scene);
        void switchScene(Scene& new_scene);

        friend class InternalDevice::Engine;
        friend class WindowX::Window;
    };



    class Scene : public Base {
    public:
        Stage* stage = nullptr;
        std::vector<GameObject::Actor*> actors;

        Scene(std::string new_sceneName);

        // A callback method of scene, calling while updating.
        // 场景更新时的回调方法。
        virtual void update();

        // A callback method of scene, calling after having switched from another scene.
        // 从另一场景切换到此场景后的回调函数。
        virtual void onEntered();

        // A callback method of scene, calling while exiting. This action will finish while returned value is "true".
        // 场景退出时的回调函数。当返回值为 "true" 时该行为完成。
        virtual bool onExiting();

        // A callback method of scene, calling while hot-key is pressed.
        // @param virtualKey The virtual key code of hot-key pressed.
        virtual void onHotkeyPressed(int virtualKey);

        // A callback method of scene, calling while hot-key is pressed.
        // @param name The name of hot-key pressed.
        virtual void onHotkeyPressed(std::string hotkeyName);

        // A callback method of scene, calling while hot-key is released.
        // @param virtualKey The virtual key code of hot-key released.
        virtual void onHotkeyReleased(int virtualKey);

        // A callback method of scene, calling while hot-key is released.
        // @param name The name of hot-key released.
        virtual void onHotkeyReleased(std::string hotkeyName);

        void registerActor(GameObject::Actor* new_actor);

        bool sendMessage(std::string actorType, std::string actorName, std::string message);
        bool sendMessage(GameObject::Actor* actor, std::string message);

    };



}
