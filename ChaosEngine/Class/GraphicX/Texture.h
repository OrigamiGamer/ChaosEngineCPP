#pragma once

#include "Class/GraphicX/GraphicX.h"



namespace Chaos::GraphicX {



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