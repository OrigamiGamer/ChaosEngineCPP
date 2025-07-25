#pragma once

#include "Common.h"

namespace Chaos::Device {
    
    Engine::Engine()
    {
        this->INIT("Engine");
    }

    Engine::~Engine()
    {

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

        this->lastEngineTime = System::getSystemTime(); // units: microseconds
        unsigned long long currentEngineTime = 0;   // units: microseconds

        //  Game Init
        if (this->engineStartupProp.onGameInit) this->engineStartupProp.onGameInit();

        // Game Loop
        unsigned long long timeSlept = 0;   // units: microseconds
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

            // FPS Control (units: microseconds)
            unsigned long long cycleTime = (1000 * 1000) / this->engineStartupProp.fps;
            timeSlept += this->deltaEngineTime;
            if (timeSlept >= cycleTime) {
                // Game Update
                engineUpdate();
                timeSlept -= cycleTime;
                if (timeSlept < 0) timeSlept = 0;
            }

            // One frame finished
            currentEngineTime = System::getSystemTime();
            this->deltaEngineTime = currentEngineTime - lastEngineTime;
            lastEngineTime = currentEngineTime;

        }
    }

    inline void Engine::start(
        unsigned int new_fps,
        Callback_GameInit new_onGameInit,
        Callback_GameExit new_onGameExit
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
        if (this->stage.has_value()) this->stage->update();

    }

    void Engine::stop()
    {
        // glfwSetWindowShouldClose(this->window->_glfwWindow, true);
        this->gameRunningState = false;
    }

    void Engine::release()
    {
        this->stage.release();

        this->renderer.release();

        this->window.release();
        glfwTerminate();

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

    bool Engine::createRenderer(Chaos::shared_ptr<Graphic::Renderer>* out_renderer)
    {
        if (!this->renderer.has_value()) {
            this->renderer = new Graphic::Renderer(this);
            if (this->window.has_value()) this->renderer->initialize(this->window.get());
            if (out_renderer != nullptr) out_renderer = &this->renderer;
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
        if (!this->createWindow()) return false;
        if (!this->createRenderer()) return false;
        if (!this->createStage()) return false;
        return true;
    }

}