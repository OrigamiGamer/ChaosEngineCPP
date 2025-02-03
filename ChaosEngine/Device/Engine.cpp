#pragma once

#include "Common.h"

namespace Chaos::Device {
    Engine::Engine()
    {
        this->stage = nullptr;
        this->window = nullptr;
        this->renderer = nullptr;
    }

    Engine::~Engine()
    {

    }

    bool Engine::createRenderer(Chaos::ptr<Graphic::Renderer>* out_renderer)
    {
        if (!this->renderer.has_value()) {
            this->renderer = new Graphic::Renderer();
            return true;
        }
        return false;
    }

    bool Engine::createRenderer()
    {
        return this->createRenderer(nullptr);
    }

    void Engine::release()
    {
        renderer.release();
    }
}