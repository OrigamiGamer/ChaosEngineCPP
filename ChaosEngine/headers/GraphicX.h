#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace GraphicX {

        extern Type::COLOR base_color;
        extern std::vector<Type::COLOR> vec_color;
        extern ID2D1SolidColorBrush* pBrush;
        extern float _strokeWidth;

        LRESULT GraphicXInit();
        inline void GraphicXRelease();

        inline void SetBrushBaseColor(Type::COLOR new_base_color);
        inline void SetStrokeWidth(FLOAT new_strokeWidth);
        inline void PushColor(Type::COLOR new_color);
        inline void PopColor();

        inline void DrawLine(Type::POS pos_1, Type::POS pos_2);
        inline void DrawRectangle(Type::POS pos, Type::SIZE size, Type::POS radius);
        inline void DrawTexture(Type::Texture*& pTexture, D2D_RECT_F rect, FLOAT opacity);
        inline void DrawTexture(Type::Texture*& pTexture, Type::POS pos, Type::SIZE size, FLOAT opacity);
        inline HRESULT DrawRawText(std::wstring content, Type::TextFormat& textFormat, Type::POS pos);
        inline HRESULT DrawRawText(Type::TextFormat& textFormat, Type::POS pos);

    }

}
