#pragma once

#include "Class/GraphicX/GraphicX.h"

namespace Chaos::GraphicX {



    // RenderTaskParam

    RenderTaskParam_Line::RenderTaskParam_Line(
        vec2<float> pos1,
        vec2<float> pos2,
        float strokeWidth,
        float opacity,
        vec2<float> pivot,
        float rotation,
        vec2<float> scale
    ) :
        pos1(pos1),
        pos2(pos2),
        strokeWidth(strokeWidth),
        opacity(opacity),
        pivot(pivot),
        rotation(rotation),
        scale(scale)
    {
        if (pivot.x == -1) this->pivot.x = pos1.x + (pos2.x - pos1.x) / 2;
        if (pivot.y == -1) this->pivot.y = pos1.y + (pos2.y - pos1.y) / 2;

    }



    RenderTaskParam_Rectangle::RenderTaskParam_Rectangle(
        vec2<float> pos,
        vec2<float> size,
        bool isFilled,
        float strokeWidth,
        vec2<float> radius,
        float opacity,
        vec2<float> pivot,
        float rotation,
        vec2<float> scale
    ) :
        pos(pos),
        size(size),
        isFilled(isFilled),
        strokeWidth(strokeWidth),
        radius(radius),
        opacity(opacity),
        pivot(pivot),
        rotation(rotation),
        scale(scale)
    {
        if (pivot.x == -1) this->pivot.x = pos.x + size.x / 2;
        if (pivot.y == -1) this->pivot.y = pos.y + size.y / 2;

    }



    RenderTaskParam_Ellipse::RenderTaskParam_Ellipse(
        vec2<float> pos,
        vec2<float> radius,
        bool isFilled,
        float strokeWidth,
        float opacity,
        vec2<float> pivot,
        float rotation,
        vec2<float> scale
    ) :
        pos(pos),
        radius(radius),
        isFilled(isFilled),
        strokeWidth(strokeWidth),
        opacity(opacity),
        pivot(pivot),
        rotation(rotation),
        scale(scale)
    {
        if (pivot.x == -1) this->pivot.x = pos.x;
        if (pivot.y == -1) this->pivot.y = pos.y;

    }



    RenderTaskParam_Texture::RenderTaskParam_Texture(
        vec2<float> pos,
        Texture* texture,
        vec2<float> size,
        vec2<float> texturePos,
        vec2<float> textureSize,
        float opacity,
        vec2<float> pivot,
        float rotation,
        vec2<float> scale
    ) :
        pos(pos),
        texture(texture),
        size(size),
        texturePos(texturePos),
        textureSize(textureSize),
        opacity(opacity),
        pivot(pivot),
        rotation(rotation),
        scale(scale)
    {
        if (texture) {
            auto _texSize = texture->getSize();

            if (size.x == -1) this->size.x = _texSize.x;
            if (size.y == -1) this->size.y = _texSize.y;

            if (textureSize.x == -1) this->textureSize.x = _texSize.x;
            if (textureSize.y == -1) this->textureSize.y = _texSize.y;

            if (pivot.x == -1) this->pivot.x = pos.x + size.x / 2;
            if (pivot.y == -1) this->pivot.y = pos.y + size.y / 2;

        }
    }



}