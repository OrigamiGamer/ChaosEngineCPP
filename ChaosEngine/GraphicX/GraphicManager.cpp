#pragma once

#include "GraphicX/GraphicX.h"

namespace Chaos::GraphicX {



    GraphicManager::GraphicManager()
    {
        this->INIT("GraphicManager");
    }



    void GraphicManager::registerRenderer(GraphicX::Renderer* new_renderer)
    {
        for (auto& renderer : GraphicManager::renderers) if (renderer->name == new_renderer->name) return;
        GraphicManager::renderers.push_back(new_renderer);
    }



    void GraphicManager::registerRenderer(GraphicX::Renderer& new_renderer)
    {
        GraphicManager::registerRenderer(&new_renderer);
    }



}