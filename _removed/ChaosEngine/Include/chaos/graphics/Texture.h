#pragma once

#include "chaos/graphics/graphics.h"


namespace chaos::graphics {



    class Texture : public Resource {
    private:
        ID2D1Bitmap** _bitmap = nullptr;

        Texture(ID2D1Bitmap** in_bitmap);

    public:
        Texture();
        ~Texture();

        Texture(Texture&&) = default;
        Texture& operator=(Texture&&) = default;

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        void release();

        vec2<float> getSize();

        friend class Renderer;

    };



}