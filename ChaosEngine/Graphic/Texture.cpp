#pragma once

#include "Common.h"

namespace Chaos::Graphic {

    Texture::Texture(ID2D1Bitmap** new_bitmap)
    {
        this->_bitmap = new_bitmap;
    }

    Texture::Texture()
    {

    }

    Texture::~Texture()
    {

    }

    vec2<float> Texture::getSize()
    {
        if (!this->_bitmap && !*this->_bitmap) return vec2<float>({ 0, 0 });
        auto& __bitmap = *this->_bitmap;
        return vec2<float>({ __bitmap->GetSize().width, __bitmap->GetSize().height });
    }

}