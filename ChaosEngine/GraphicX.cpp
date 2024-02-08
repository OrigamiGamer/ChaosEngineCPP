#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    // Basic Interfaces of Graphics
    namespace GraphicX {

        ID2D1SolidColorBrush* pBrush = nullptr;
        float StrokeWidth = 1;

        LRESULT GraphicXInit() {
            D2D1_BRUSH_PROPERTIES brush_properties = D2D1_BRUSH_PROPERTIES();
            brush_properties.opacity = 1;
            brush_properties.transform = D2D1::IdentityMatrix();

            WindowX::pHwndRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::LightGreen),
                brush_properties,
                &pBrush
            );

            return 0;
        };

        LRESULT GraphicXRelease() {
            LRESULT lr = NULL;
            lr = pBrush->Release();
            return lr;
        };

        void SetBrushColor(Type::COLOR newColor) {
            pBrush->SetColor(D2D1::ColorF(newColor.rgb, newColor.alpha));
        };

        void SetStrokeWidth(FLOAT newStrokeWidth) {
            if (newStrokeWidth >= 0) StrokeWidth = newStrokeWidth;
        };

        void DrawLine(Type::POS pos_1, Type::POS pos_2) {
            WindowX::pHwndRenderTarget->DrawLine({ pos_1.x, pos_1.y }, { pos_2.x, pos_2.y }, pBrush, StrokeWidth);
        };

        void DrawRectangle(Type::POS pos, Type::SIZE size, Type::POS radius = { 0, 0 }) {
            D2D1_RECT_F rect{ pos.x, pos.y, pos.x + size.width, pos.y + size.height };
            if (radius.x == 0 && radius.y == 0) {
                WindowX::pHwndRenderTarget->DrawRectangle(rect, pBrush, StrokeWidth);
            }
            else {
                WindowX::pHwndRenderTarget->DrawRoundedRectangle(
                    D2D1::RoundedRect(rect, radius.x, radius.y),
                    pBrush,
                    StrokeWidth
                );
            }
        };

        void DrawTexture(Type::Texture*& pTexture, D2D_RECT_F rect, FLOAT opacity = 1.0F) {
            const auto mode = D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;  // As a setting of GraphicX
            WindowX::pHwndRenderTarget->DrawBitmap(pTexture->pD2DBitmap, rect, opacity, mode);
        };
        inline void DrawTexture(Type::Texture*& pTexture, Type::POS pos, Type::SIZE size, FLOAT opacity = 1.0F) {
            const D2D1_RECT_F rect{ pos.x, pos.y, pos.x + size.width, pos.y + size.height };
            DrawTexture(pTexture, rect, opacity);
        };

    }

}
