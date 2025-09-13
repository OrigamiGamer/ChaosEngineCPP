#pragma once

#include "Class/GraphicX/GraphicX.h"



namespace Chaos::GraphicX {



    class Viewport : public Base {
    private:
        ID2D1Bitmap* _bitmap = nullptr;

    public:
        Renderer* renderer = nullptr;

        Chaos::vec2<float> viewPos{};
        Chaos::vec2<float> viewSize{};

        Chaos::vec2<float> pos{};
        Chaos::vec2<float> size{};
        Chaos::vec2<float> pivot{};
        float rotation = 0.0f;
        float opacity = 1.0f;

        Viewport();

        void release();

        friend class Renderer;

    };



}