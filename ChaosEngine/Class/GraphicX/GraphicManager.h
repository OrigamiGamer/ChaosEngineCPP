#pragma once

#include "Class/GraphicX/GraphicX.h"



namespace Chaos::GraphicX {



    class GraphicManager : public Base {
    public:
        static std::vector<GraphicX::Renderer*> s_renderers;

        GraphicManager();

        static void registerRenderer(GraphicX::Renderer* new_renderer);
        static void registerRenderer(GraphicX::Renderer& new_renderer);

    };



}