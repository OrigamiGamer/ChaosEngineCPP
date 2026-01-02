#pragma once

#include "Class/Graphics/Graphics.h"



namespace Chaos::Graphics {



    class Texture : public Resource {
    private:
        ID2D1Bitmap** _bitmap = nullptr;

        Texture(ID2D1Bitmap** new_bitmap);

    public:
        Texture();
        ~Texture();

        void release();

        vec2<float> getSize();

        friend class Renderer;

    };



}