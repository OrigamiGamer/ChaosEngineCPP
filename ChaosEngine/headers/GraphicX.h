#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace GraphicX {

        extern ID2D1SolidColorBrush* pBrush;
        extern float StrokeWidth;

        LRESULT GraphicXInit();
        void GraphicXRelease();
        void SetBrushColor(Type::COLOR newColor);
        void SetStrokeWidth(FLOAT newStrokeWidth);
        void DrawLine(Type::POS pos_1, Type::POS pos_2);
        void DrawRectangle(Type::POS pos, Type::SIZE size, Type::POS radius);
        void DrawTexture(Type::Texture*& pTexture, D2D_RECT_F rect, FLOAT opacity);
        inline void DrawTexture(Type::Texture*& pTexture, Type::POS pos, Type::SIZE size, FLOAT opacity);
        HRESULT DrawTextRaw(std::wstring content, std::wstring fontFamilyName, FLOAT fontSize, Type::SIZE layoutSize, Type::POS pos);
        HRESULT DrawTextRaw(Type::TextFormat textFormat, Type::POS pos);

    }

}
