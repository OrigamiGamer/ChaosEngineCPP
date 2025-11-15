#pragma once

#include "Class/InternalDevice/InternalDevice.h"



namespace Chaos::InternalDevice {



    class Stage : public Device {
    private:
        std::vector<Scene*> _scenes;
        Scene* _currentScene = nullptr;
        Scene* _preparedScene = nullptr;
        Log::Logger _logger;

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



}