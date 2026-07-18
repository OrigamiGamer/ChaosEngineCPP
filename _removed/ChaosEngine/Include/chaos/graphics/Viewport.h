#pragma once

#include "chaos/graphics/graphics.h"


namespace chaos::graphics {



    class Viewport : public Base {
    private:
        ID2D1Bitmap* _bitmap = nullptr;

    public:
        Renderer* renderer = nullptr;

        chaos::vec2<float> viewPos{};
        chaos::vec2<float> viewSize{};

        chaos::vec2<float> pos{};
        chaos::vec2<float> size{};
        chaos::vec2<float> pivot{};
        float rotation = 0.0f;
        float opacity = 1.0f;

        Viewport();

        void release();

        friend class Renderer;

    };



}