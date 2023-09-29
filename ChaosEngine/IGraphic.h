#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace IGraphic {

        extern ID2D1SolidColorBrush* pBrush;
        extern float StrokeWidth;

        LRESULT Init();
        LRESULT Release();
        void SetColor(Type::COLOR newColor);
        void SetStrokeWidth(FLOAT newStrokeWidth);
        void DrawLine(Type::POS pos_1, Type::POS pos_2);
        void DrawRectangle(Type::POS pos, Type::SIZE size, Type::POS radius);
        void DrawTexture(Type::POS pos, Type::SIZE size, FLOAT opacity);

    }

}
