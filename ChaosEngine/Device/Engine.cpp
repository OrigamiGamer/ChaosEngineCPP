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
        // (至少现在，也许我们不需要 设备对象共享 [?])
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

    bool Engine::createWindow(Chaos::shared_ptr<Device::Window>* out_window)
    {
        if (!this->window.has_value()) {
            this->window = new Device::Window(this);
            if (out_window != nullptr) out_window = &this->window;
            return true;
        }
        return false;
    }

    void Engine::initialize()
    {
        this->createRenderer();
        this->createWindow();
    }

    void Engine::release()
    {
        this->renderer.release();
        this->window.release();
        this->stage.release();
    }
}