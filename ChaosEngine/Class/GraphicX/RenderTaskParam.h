#pragma once

#include "Class/GraphicX/GraphicX.h"



namespace Chaos::GraphicX {



    // Parameters of task types:



    // Line
    struct RenderTaskParam_Line {
        vec2<float> pos1{};
        vec2<float> pos2{};
        float strokeWidth = 1.0f;
        float opacity = 1.0f;
        vec2<float> pivot = { 0.0f,0.0f };
        float rotation = 0.0f;
        vec2<float> scale = { 1.0f,1.0f };

        RenderTaskParam_Line(
            vec2<float> pos1,
            vec2<float> pos2,
            float strokeWidth = 1.0f,
            float opacity = 1.0f,
            vec2<float> pivot = { 0.0f,0.0f },
            float rotation = 0.0f,
            vec2<float> scale = { 1.0f,1.0f }
        );

    };



    // Texture
    // If the parameter "size" or "textureSize" is the default or any of their components equals "-1",
    // they will be set to the texture's size.
    // 如果参数 "size" 或 "textureSize" 为默认值，或它们的任何分量等于 "-1"，它们将被设置为纹理尺寸。
    struct RenderTaskParam_Texture {
        vec2<float> pos{};
        vec2<float> size{ -1,-1 };
        vec2<float> texturePos{};
        vec2<float> textureSize{ -1,-1 };
        Texture* texture = nullptr;
        float opacity = 1.0f;
        vec2<float> pivot = { 0.0f,0.0f };
        float rotation = 0.0f;
        vec2<float> scale = { 1.0f,1.0f };

        RenderTaskParam_Texture(
            vec2<float> pos,
            Texture* texture,
            vec2<float> size = { -1,-1 },
            vec2<float> texturePos = { 0.0f,0.0f },
            vec2<float> textureSize = { -1,-1 },
            float opacity = 1.0f,
            vec2<float> pivot = { 0.0f,0.0f },
            float rotation = 0.0f,
            vec2<float> scale = { 1.0f,1.0f }
        );

    };



}