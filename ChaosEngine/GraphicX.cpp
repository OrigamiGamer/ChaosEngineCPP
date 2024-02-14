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
        }

        void GraphicXRelease() {
            SafeRelease(&pBrush);
        }

        void SetBrushColor(Type::COLOR newColor) {
            pBrush->SetColor(D2D1::ColorF(newColor.rgb, newColor.alpha));
        }
        void SetStrokeWidth(FLOAT newStrokeWidth) {
            if (newStrokeWidth >= 0) StrokeWidth = newStrokeWidth;
        }

        void DrawLine(Type::POS pos_1, Type::POS pos_2) {
            WindowX::pHwndRenderTarget->DrawLine({ pos_1.x, pos_1.y }, { pos_2.x, pos_2.y }, pBrush, StrokeWidth);
        }

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
        }

        inline void DrawTexture(Type::Texture*& pTexture, D2D_RECT_F rect, FLOAT opacity = 1.0F) {
            const auto mode = D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;  // As a setting of GraphicX
            WindowX::pHwndRenderTarget->DrawBitmap(pTexture->pD2DBitmap, rect, opacity, mode);
        }
        void DrawTexture(Type::Texture*& pTexture, Type::POS pos, Type::SIZE size, FLOAT opacity = 1.0F) {
            const D2D1_RECT_F rect{ pos.x, pos.y, pos.x + size.width, pos.y + size.height };
            DrawTexture(pTexture, rect, opacity);
        }

        HRESULT DrawRawText(std::wstring content, std::wstring fontFamilyName, FLOAT fontSize, Type::SIZE layoutSize, Type::POS pos) {
            HRESULT hr = NULL;

            static IDWriteTextFormat* pTextFormat = nullptr;
            static IDWriteTextLayout* pTextLayout = nullptr;

            // format
            DWRITE_FONT_WEIGHT font_weight = DWRITE_FONT_WEIGHT_NORMAL;
            DWRITE_FONT_STYLE font_style = DWRITE_FONT_STYLE_NORMAL;
            DWRITE_FONT_STRETCH font_stretch = DWRITE_FONT_STRETCH_NORMAL;
            std::wstring local_name = L"zh";    //

            static std::wstring _content;
            static std::wstring _fontFamilyName;
            static FLOAT _fontSize;
            static Type::SIZE _layoutSize;

            static bool state_update = false;
            state_update = _content != content || _fontFamilyName != fontFamilyName || _fontSize != fontSize;
            state_update = state_update || _layoutSize.width != layoutSize.width || _layoutSize.height != layoutSize.height;

            if (state_update) {
                _content = content;
                _fontFamilyName = fontFamilyName;
                _fontSize = fontSize;
                _layoutSize = layoutSize;

                SafeRelease(&pTextFormat);
                SafeRelease(&pTextLayout);

                hr = WindowX::pDWriteFactory->CreateTextFormat(
                    fontFamilyName.c_str(),
                    NULL,
                    font_weight,
                    font_style,
                    font_stretch,
                    fontSize,
                    local_name.c_str(),
                    &pTextFormat
                );

                if (pTextFormat) {
                    hr = WindowX::pDWriteFactory->CreateTextLayout(
                        content.c_str(),
                        (UINT32)content.size(),
                        pTextFormat,
                        layoutSize.width,
                        layoutSize.height,
                        &pTextLayout
                    ); if (FAILED(hr)) return hr;
                }
                else return hr;
            }

            WindowX::pHwndRenderTarget->DrawTextLayout(
                { pos.x, pos.y },
                pTextLayout,
                pBrush,
                D2D1_DRAW_TEXT_OPTIONS_NONE
            );
            

            return hr;
        }
        HRESULT DrawRawText(std::wstring content, Type::TextFormat& textFormat, Type::POS pos) {
            textFormat.SetContent(content);
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
