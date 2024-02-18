#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    // Basic Interfaces of Graphics
    namespace GraphicX {
        Type::COLOR base_color = { D2D1::ColorF::LightPink, 1 };
        std::vector<Type::COLOR> vec_color;
        ID2D1SolidColorBrush* pBrush = nullptr;
        float _strokeWidth = 1;

        // Initialize
        LRESULT GraphicXInit() {
            D2D1_BRUSH_PROPERTIES brush_properties = D2D1_BRUSH_PROPERTIES();
            brush_properties.opacity = 1;
            brush_properties.transform = D2D1::IdentityMatrix();

            WindowX::pHwndRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(base_color.rgb),
                brush_properties,
                &pBrush
            );

            return 0;
        }

        // Release
        inline void GraphicXRelease() {
            SafeRelease(&pBrush);
        }

        // Set a base color to the brush.
        inline void SetBrushBaseColor(Type::COLOR new_base_color) {
            base_color = new_base_color;
            pBrush->SetColor(D2D1::ColorF(base_color.rgb, base_color.alpha));
        }
        // Set a stroke width to the brush.
        inline void SetStrokeWidth(FLOAT new_strokeWidth) {
            if (new_strokeWidth < 0) new_strokeWidth = 0; _strokeWidth = new_strokeWidth;
        }
        // Push a color to the top of the color heap.
        inline void PushColor(Type::COLOR new_color) {
            vec_color.push_back(new_color);
            pBrush->SetColor(D2D1::ColorF(new_color.rgb, new_color.alpha));
        }
        // Pop a color which pushed last time from the top of the color heap.
        inline void PopColor() {
            vec_color.pop_back();
            if (vec_color.size() > 0) {
                Type::COLOR& _back = vec_color.back();
                pBrush->SetColor(D2D1::ColorF(_back.rgb, _back.alpha));
            }
            else {
                pBrush->SetColor(D2D1::ColorF(base_color.rgb, base_color.alpha));
            }
        }

        // Draw a line.
        inline void DrawLine(Type::POS pos_1, Type::POS pos_2) {
            WindowX::pHwndRenderTarget->DrawLine({ pos_1.x, pos_1.y }, { pos_2.x, pos_2.y }, pBrush, _strokeWidth);
        }

        // Draw a rectangle.
        inline void DrawRectangle(Type::POS pos, Type::SIZE size, Type::POS radius = { 0, 0 }) {
            D2D1_RECT_F rect{ pos.x, pos.y, pos.x + size.width, pos.y + size.height };
            if (radius.x == 0 && radius.y == 0) {
                WindowX::pHwndRenderTarget->DrawRectangle(rect, pBrush, _strokeWidth);
            }
            else {
                WindowX::pHwndRenderTarget->DrawRoundedRectangle(
                    D2D1::RoundedRect(rect, radius.x, radius.y),
                    pBrush,
                    _strokeWidth
                );
            }
        }

        // Draw a texture.
        inline void DrawTexture(Type::Texture*& pTexture, D2D_RECT_F rect, FLOAT opacity = 1.0F) {
            const auto mode = D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;  // As a setting of GraphicX
            WindowX::pHwndRenderTarget->DrawBitmap(pTexture->pD2DBitmap, rect, opacity, mode);
        }
        inline void DrawTexture(Type::Texture*& pTexture, Type::POS pos, Type::SIZE size, FLOAT opacity = 1.0F) {
            const D2D1_RECT_F rect{ pos.x, pos.y, pos.x + size.width, pos.y + size.height };
            DrawTexture(pTexture, rect, opacity);
        }

        // Draw a piece of raw text.
        inline HRESULT DrawRawText(std::wstring content, Type::TextFormat& textFormat, Type::POS pos) {
            textFormat.SetContent(content);
            WindowX::pHwndRenderTarget->DrawTextLayout(
                { pos.x, pos.y },
                textFormat.pLayout,
                pBrush,
                D2D1_DRAW_TEXT_OPTIONS_NONE //
            );
            return S_OK;
        }
        inline HRESULT DrawRawText(Type::TextFormat& textFormat, Type::POS pos) {
            WindowX::pHwndRenderTarget->DrawTextLayout(
                { pos.x, pos.y },
                textFormat.pLayout,
                pBrush,
                D2D1_DRAW_TEXT_OPTIONS_NONE //
            );
            return S_OK;
        }


    }

}
