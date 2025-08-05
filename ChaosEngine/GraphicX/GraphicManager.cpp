#pragma once

#include "GraphicX/GraphicX.h"

namespace Chaos::GraphicX {



    std::vector<Renderer*> GraphicManager::s_renderers;



    GraphicManager::GraphicManager()
    {
        this->INIT("GraphicManager");
    }



    void GraphicManager::registerRenderer(GraphicX::Renderer* new_renderer)
    {
        for (auto& renderer : GraphicManager::s_renderers) if (renderer->name == new_renderer->name) return;
        GraphicManager::s_renderers.push_back(new_renderer);
    }



    void GraphicManager::registerRenderer(GraphicX::Renderer& new_renderer)
    {
        GraphicManager::registerRenderer(&new_renderer);
    }



}