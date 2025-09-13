#pragma once

#include "Class/InternalDevice/InternalDevice.h"

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

            // window update
            windowUpdate();

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



    void Engine::windowUpdate()
    {
        if (this->stage) this->stage->_updateWindow();
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
        glfwTerminate();

        // Renderer
        this->renderer->release();

    }



    void Engine::registerRenderer(GraphicX::Renderer* new_renderer)
    {
        if (this->renderer) this->renderer->engine = nullptr;
        new_renderer->engine = this;
        this->renderer = new_renderer;
    }



    void Engine::registerStage(InternalDevice::Stage* new_stage)
    {
        if (this->stage) this->stage->engine = nullptr;
        new_stage->engine = this;
        this->stage = new_stage;
    }



}