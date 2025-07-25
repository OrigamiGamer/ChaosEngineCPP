#pragma once

#include "InternalDevice/InternalDevice.h"

namespace Chaos::InternalDevice {



    Engine::Engine()
    {
        this->INIT("Engine");

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
        // store startup property of engine
        if (new_engineStartupProp) {
            // custom property
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

        //  game init
        if (this->engineStartupProp.onGameInit) this->engineStartupProp.onGameInit();

        // game loop
        unsigned long long timeSlept = 0;   // units: microseconds
        while (this->gameRunningState) {

            // handle window message
            if (this->window) {
                auto& _glfwWindow = this->window->_glfwWindow;
                if (!glfwWindowShouldClose(_glfwWindow)) {
                    glfwSwapBuffers(_glfwWindow);
                    glfwPollEvents();
                }
                else {
                    // game exit
                    if (this->engineStartupProp.onGameExit ? this->engineStartupProp.onGameExit() : true) {
                        // user confirmed
                        break;
                    }
                    // user denied
                    glfwSetWindowShouldClose(_glfwWindow, false);
                }
            }

            // FPS control (units: microseconds)
            unsigned long long cycleTime = (1000 * 1000) / this->engineStartupProp.fps;
            timeSlept += this->deltaEngineTime;
            if (timeSlept >= cycleTime) {
                // game update
                engineUpdate();
                timeSlept -= cycleTime;
                if (timeSlept < 0) timeSlept = 0;
            }

            // one frame finished
            currentEngineTime = System::getSystemTime();
            this->deltaEngineTime = currentEngineTime - lastEngineTime;
            lastEngineTime = currentEngineTime;

        }
    }



    void Engine::start(
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
        if (this->stage) this->stage->update();

    }



    void Engine::stop()
    {
        // glfwSetWindowShouldClose(this->window->_glfwWindow, true);
        this->gameRunningState = false;
    }



    void Engine::release()
    {
        // Stage
        this->stage->release();

        // Renderer
        this->renderer->release();

        // Window
        this->window->release();
        glfwTerminate();

    }



    bool Engine::createWindow(WindowX::WindowProperty* new_windowProp, std::shared_ptr<WindowX::Window>* out_window)
    {
        if (!this->window) {
            this->window.reset(new WindowX::Window(this));
            if (out_window != nullptr) out_window = &this->window;
            this->window->initialize(new_windowProp);
            glfwMakeContextCurrent(this->window->_glfwWindow);
            return true;
        }
        return false;
    }



    bool Engine::createRenderer(std::shared_ptr<GraphicX::Renderer>* out_renderer)
    {
        if (!this->renderer) {
            this->renderer.reset(new GraphicX::Renderer(this));
            if (this->window) this->renderer->initialize(this->window.get());
            if (out_renderer != nullptr) out_renderer = &this->renderer;
            return true;
        }
        return false;
    }



    bool Engine::createStage(std::shared_ptr<InternalDevice::Stage>* out_stage)
    {
        if (!this->stage) {
            this->stage.reset(new InternalDevice::Stage(this));
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