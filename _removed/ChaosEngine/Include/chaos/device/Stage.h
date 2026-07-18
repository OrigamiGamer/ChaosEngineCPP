#pragma once

#include "chaos/device/device.h"


namespace chaos::device {



    class Stage : public Device {
    private:
        std::vector<Scene*> _scenes;
        Scene* _currentScene = nullptr;
        Scene* _preparedScene = nullptr;

        log::Logger _logger;

        void _updateWindow();

    public:
        std::vector<chaos::windows::Window*> windows;

        Stage();

        void release();

        void registerWindow(windows::Window* in_window);
        void registerWindow(windows::Window& in_window);

        void unregisterWindow(std::string windowTitle, std::string windowName = "");
        void unregisterWindow(windows::Window& in_window);
        void unregisterWindow(windows::Window* in_window);

        void update();
        
        void registerScene(Scene* in_scene);
        void registerScene(Scene& in_scene);

        bool switchScene(std::string in_sceneName);
        void switchScene(Scene* in_scene);
        void switchScene(Scene& in_scene);

        friend class device::Engine;
        friend class windows::Window;
    };



}