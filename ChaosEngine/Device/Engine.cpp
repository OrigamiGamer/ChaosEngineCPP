#pragma once

#include "Common.h"

namespace Chaos::Device {
    Engine::Engine()
    {
        this->INIT("Engine");
        this->renderer = nullptr;
        this->window = nullptr;
        this->stage = nullptr;
    }

    Engine::~Engine()
    {
        // !! 任何 设备对象 都必须隶属于特定 引擎对象，所以 设备对象共享 将不可用。(多窗口对象共享 将不可用!) !!
        // 可行措施: 设备对象控制权 交予 用户，而非 引擎对象...
        // ( 也许至少现在，我们并不奢求 共享设备对象 ? )
    }

    bool Engine::initialize()
    {
        // initialize GLFW
        if (!glfwInit()) return false;
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        this->gameRunningState = true;

        return true;
    }

    void Engine::start(EngineStartupProperty* new_engineStartupProp)
    {
        if (new_engineStartupProp) {
            // user property
            this->engineStartupProp = *new_engineStartupProp;
        }
        else {
            // default property
            this->engineStartupProp.fps = 60;
            this->engineStartupProp.onGameInit = nullptr;
            this->engineStartupProp.onGameExit = []()-> bool {return true;};
        }

        this->lastEngineTime = System::getSystemTime();
        unsigned long long currentEngineTime = 0;

        //  Game Init
        if (this->engineStartupProp.onGameInit) this->engineStartupProp.onGameInit();

        // Game Loop
        while (this->gameRunningState) {

            // Handle Window Message
            if (this->window.has_value()) {
                auto& _glfwWindow = this->window->_glfwWindow;
                if (!glfwWindowShouldClose(_glfwWindow)) {
                    glfwSwapBuffers(_glfwWindow);
                    glfwPollEvents();
                }
                else {
                    // Game Exit
                    if (this->engineStartupProp.onGameExit()) {
                        // user confirmed
                        break;
                    }
                    // user denied
                    glfwSetWindowShouldClose(_glfwWindow, false);
                }
            }

            // Game Update
            engineUpdate();

            // One frame finished
            currentEngineTime = System::getSystemTime();
            this->deltaEngineTime = currentEngineTime - lastEngineTime;
            lastEngineTime = currentEngineTime;

        }
    }

    inline void Engine::start(
        unsigned int new_fps = 60,
        Callback_GameInit new_onGameInit = nullptr,
        Callback_GameExit new_onGameExit = nullptr
    )
    {
        EngineStartupProperty new_engineStartupProp;
        new_engineStartupProp.fps = new_fps;
        new_engineStartupProp.onGameInit = new_onGameInit;
        new_engineStartupProp.onGameExit = new_onGameExit;
        this->start(&new_engineStartupProp);
    }

    void Engine::engineUpdate()
    {
        this->stage->update();
    }

    void Engine::stop()
    {
        // glfwSetWindowShouldClose(this->window->_glfwWindow, true);
        this->gameRunningState = false;
    }

    void Engine::release()
    {
        this->stage.release();

        this->window.release();
        glfwTerminate();

        this->renderer.release();

    }

    bool Engine::createRenderer(Chaos::shared_ptr<Graphic::Renderer>* out_renderer)
    {
        if (!this->renderer.has_value()) {
            this->renderer = new Graphic::Renderer(this);
            if (out_renderer != nullptr) out_renderer = &this->renderer;
            return true;
        }
        return false;
    }

    bool Engine::createWindow(Device::WindowProperty* new_windowProp, Chaos::shared_ptr<Device::Window>* out_window)
    {
        if (!this->window.has_value()) {
            this->window = new Device::Window(this);
            if (out_window != nullptr) out_window = &this->window;
            this->window->initialize(new_windowProp);
            glfwMakeContextCurrent(this->window->_glfwWindow);
            return true;
        }
        return false;
    }

    bool Engine::createStage(Chaos::shared_ptr<Content::Stage>* out_stage)
    {
        if (!this->stage.has_value()) {
            this->stage = new Content::Stage(this);
            if (out_stage != nullptr) out_stage = &this->stage;
        }
        return false;
    }

    bool Engine::createDefaultDevice()
    {
        if (!this->createRenderer()) return false;
        if (!this->createWindow()) return false;
        if (!this->createStage()) return false;
        return true;
    }

}