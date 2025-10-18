#pragma once

#include "Class/GraphicX/GraphicX.h"



namespace Chaos::GraphicX {



    // Parameters of task types:



    // Line
    // @param pivot Use center position gotten from the parameters "pos1" and "pos2" by default while any direction of this parameter is "-1".
    struct RenderTaskParam_Line {
        vec2<float> pos1;
        vec2<float> pos2;
        float strokeWidth;
        float opacity;
        vec2<float> pivot;
        float rotation;
        vec2<float> scale;

        RenderTaskParam_Line(
            vec2<float> pos1 = { 0.0f,0.0f },
            vec2<float> pos2 = { 100.0f,100.0f },
            float strokeWidth = 1.0f,
            float opacity = 1.0f,
            vec2<float> pivot = { -1,-1 },
            float rotation = 0.0f,
            vec2<float> scale = { 1.0f,1.0f }
        );

    };



    // Rectangle
    // @param radius Determine that whether this rectangle is rounded or not, and how round it is.
    // @param pivot Use center position gotten from the parameters "pos" and "size" by default while any direction of this parameter is "-1".
    struct RenderTaskParam_Rectangle {
        vec2<float> pos{};
        vec2<float> size;
        bool isFilled;
        float strokeWidth;
        vec2<float> radius;
        float opacity;
        vec2<float> pivot;
        float rotation;
        vec2<float> scale;

        RenderTaskParam_Rectangle(
            vec2<float> pos = { 0.0f,0.0f },
            vec2<float> size = { 100.0f,100.0f },
            bool isFilled = false,
            float strokeWidth = 1.0f,
            vec2<float> radius = { 0.0f,0.0f },
            float opacity = 1.0f,
            vec2<float> pivot = { -1,-1 },
            float rotation = 0.0f,
            vec2<float> scale = { 1.0f,1.0f }
        );
    };



    // Ellipse
    // @param pos The center position of this ellipse.
    // @param radius The radius of this ellipse.
    // @param pivot Use center position gotten from the parameter "pos" by default while any direction of this parameter is "-1".
    struct RenderTaskParam_Ellipse {
        vec2<float> pos{};
        vec2<float> radius;
        bool isFilled;
        float strokeWidth;
        float opacity;
        vec2<float> pivot;
        float rotation;
        vec2<float> scale;

        RenderTaskParam_Ellipse(
            vec2<float> pos = { 0.0f,0.0f },
            vec2<float> radius = { 100.0f,100.0f },
            bool isFilled = false,
            float strokeWidth = 1.0f,
            float opacity = 1.0f,
            vec2<float> pivot = { -1,-1 },
            float rotation = 0.0f,
            vec2<float> scale = { 1.0f,1.0f }
        );
    };



    // Texture
    // @param size Use texture's size by default while any direction of this parameter is "-1".
    // @param textureSize Use texture's size by default while any direction of this parameter is "-1".
    // @param pivot Use center position gotten from the parameters "pos" and "size" by default while any direction of this parameter is "-1".
    struct RenderTaskParam_Texture {
        vec2<float> pos;
        vec2<float> size;
        vec2<float> texturePos;
        vec2<float> textureSize;
        Texture* texture;
        float opacity;
        vec2<float> pivot;
        float rotation;
        vec2<float> scale;

        RenderTaskParam_Texture(
            vec2<float> pos = { 0.0f,0.0f },
            Texture* texture = nullptr,
            vec2<float> size = { -1,-1 },
            vec2<float> texturePos = { 0.0f,0.0f },
            vec2<float> textureSize = { -1,-1 },
            float opacity = 1.0f,
            vec2<float> pivot = { -1,-1 },
            float rotation = 0.0f,
            vec2<float> scale = { 1.0f,1.0f }
        );

    };



}