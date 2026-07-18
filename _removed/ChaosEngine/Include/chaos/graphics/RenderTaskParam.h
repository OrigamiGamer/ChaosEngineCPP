#pragma once

#include "chaos/graphics/graphics.h"


namespace chaos::graphics {



    // Parameters of tasks:



    /**
     * @brief Line
     */
    struct RenderTaskParam_Line {
        vec2<float> pos1;
        vec2<float> pos2;
        float strokeWidth;
        float opacity;
        /** `{ -1.0f, -1.0f }` means the center position derived from `pos1` and `pos2`. */
        vec2<float> pivot;
        float rotation;
        vec2<float> scale;

        RenderTaskParam_Line(
            vec2<float> pos1 = { 0.0f, 0.0f },
            vec2<float> pos2 = { 100.0f, 100.0f },
            float strokeWidth = 1.0f,
            float opacity = 1.0f,
            vec2<float> pivot = { -1.0f, -1.0f },
            float rotation = 0.0f,
            vec2<float> scale = { 1.0f, 1.0f }
        );

    };



    /**
     * @brief Rectangle
     */
    struct RenderTaskParam_Rectangle {
        vec2<float> pos;
        vec2<float> size;
        bool isFilled;
        float strokeWidth;
        vec2<float> radius;
        float opacity;
        /** `{-1.0f, -1.0f}` means the center position derived from `pos` and `size`. */
        vec2<float> pivot;
        float rotation;
        vec2<float> scale;

        RenderTaskParam_Rectangle(
            vec2<float> pos = { 0.0f, 0.0f },
            vec2<float> size = { 100.0f, 100.0f },
            bool isFilled = false,
            float strokeWidth = 1.0f,
            vec2<float> radius = { 0.0f, 0.0f },
            float opacity = 1.0f,
            vec2<float> pivot = { -1.0f, -1.0f },
            float rotation = 0.0f,
            vec2<float> scale = { 1.0f, 1.0f }
        );
    };



    /**
     * @brief Ellipse
     */
    struct RenderTaskParam_Ellipse {
        /** Center position of the ellipse. */
        vec2<float> pos;
        vec2<float> radius;
        bool isFilled;
        float strokeWidth;
        float opacity;
        /** `{ -1.0f, -1.0f }` means center position of ellipse, also the `pos`. */
        vec2<float> pivot;
        float rotation;
        vec2<float> scale;

        RenderTaskParam_Ellipse(
            vec2<float> pos = { 0.0f, 0.0f },
            vec2<float> radius = { 100.0f, 100.0f },
            bool isFilled = false,
            float strokeWidth = 1.0f,
            float opacity = 1.0f,
            vec2<float> pivot = { -1.0f, -1.0f },
            float rotation = 0.0f,
            vec2<float> scale = { 1.0f, 1.0f }
        );
    };



    /**
     * @brief Texture
     */
    struct RenderTaskParam_Texture {
        vec2<float> pos;
        /** { -1.0f, -1.0f } uses texture's original size. */
        vec2<float> size;
        vec2<float> texturePos;
        /** { -1.0f, -1.0f } uses texture's original size. */
        vec2<float> textureSize;
        Texture* texture;
        float opacity;
        /** { -1.0f, -1.0f } means the center position derived from `pos` and `size`. */
        vec2<float> pivot;
        float rotation;
        vec2<float> scale;

        RenderTaskParam_Texture(
            vec2<float> pos = { 0.0f, 0.0f },
            Texture* texture = nullptr,
            vec2<float> size = { -1.0f, -1.0f },
            vec2<float> texturePos = { 0.0f, 0.0f },
            vec2<float> textureSize = { -1.0f, -1.0f },
            float opacity = 1.0f,
            vec2<float> pivot = { -1.0f, -1.0f },
            float rotation = 0.0f,
            vec2<float> scale = { 1.0f, 1.0f }
        );

    };



}