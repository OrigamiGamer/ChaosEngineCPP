#pragma once

#include "Common.h"

namespace Chaos::Graphic {

    Texture::Texture()
    {

    }

    Texture::~Texture()
    {
        
    }

    vec2<float> Texture::getSize()
    {
        if (!this->_bitmap.has_value()) return vec2<float>(0, 0);
        return this->_bitmap.get()->getSize();
    }

}