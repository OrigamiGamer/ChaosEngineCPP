#include "chaos/graphics/graphics.h"

namespace chaos::graphics {



    std::vector<Renderer*> GraphicManager::s_renderers;



    GraphicManager::GraphicManager()
    {
        this->INIT("GraphicManager");
    }



    void GraphicManager::registerRenderer(graphics::Renderer* in_renderer)
    {
        for (auto& renderer : GraphicManager::s_renderers) if (renderer->nameId == in_renderer->nameId) return;
        GraphicManager::s_renderers.push_back(in_renderer);
    }



    void GraphicManager::registerRenderer(graphics::Renderer& in_renderer)
    {
        GraphicManager::registerRenderer(&in_renderer);
    }



}