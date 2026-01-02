#pragma once

#include "Class/Graphics/Graphics.h"

namespace Chaos::Graphics {



    std::vector<Renderer*> GraphicManager::s_renderers;



    GraphicManager::GraphicManager()
    {
        this->INIT("GraphicManager");
    }



    void GraphicManager::registerRenderer(Graphics::Renderer* new_renderer)
    {
        for (auto& renderer : GraphicManager::s_renderers) if (renderer->nameId == new_renderer->nameId) return;
        GraphicManager::s_renderers.push_back(new_renderer);
    }



    void GraphicManager::registerRenderer(Graphics::Renderer& new_renderer)
    {
        GraphicManager::registerRenderer(&new_renderer);
    }



}