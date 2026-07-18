#pragma once

#include "chaos/graphics/graphics.h"


namespace chaos::graphics {



    class GraphicManager : public Base {
    public:
        static std::vector<graphics::Renderer*> s_renderers;

        GraphicManager();

        static void registerRenderer(graphics::Renderer* in_renderer);
        static void registerRenderer(graphics::Renderer& in_renderer);

    };



}