#pragma once

#include "Class/Graphics/Graphics.h"



namespace Chaos::Graphics {



    class GraphicManager : public Base {
    public:
        static std::vector<Graphics::Renderer*> s_renderers;

        GraphicManager();

        static void registerRenderer(Graphics::Renderer* new_renderer);
        static void registerRenderer(Graphics::Renderer& new_renderer);

    };



}