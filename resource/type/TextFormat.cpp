#pragma once
#include "_list.h"

namespace ChaosEngine {

    namespace Type {

        TextFormat::TextFormat() {
            s_content;
            s_local_name;
            s_font_family_name;
            s_layout_size = { 600, 600 };
            pFormat = nullptr;
            pLayout = nullptr;
        }

        void TextFormat::Init() {
            Initialize();
        }

        // Release the memory of Format and Layout objects safely.
        void TextFormat::Release() {
            SafeRelease(&pFormat);
            SafeRelease(&pLayout);
        }

        // Update the properties and recreate the Format and Layout objects.
        HRESULT TextFormat::_update(
            DWRITE_FONT_WEIGHT font_weight,
            DWRITE_FONT_STYLE font_style,
            DWRITE_FONT_STRETCH font_stretch,
            std::wstring local_name,
            std::wstring content,
            std::wstring font_family_name,
            FLOAT font_size,
            Type::SIZE layout_size
        ) {
            Release();
            HRESULT hr = S_OK;

            // update cached properties
            if (s_content != content) s_content = content;
            if (s_local_name != local_name) s_local_name = local_name;
            if (s_font_family_name != font_family_name) s_font_family_name = font_family_name;
            if (s_layout_size.height != layout_size.height || s_layout_size.width != layout_size.width) s_layout_size = layout_size;

            hr = DirectX::pDWriteFactory->CreateTextFormat(
                font_family_name.c_str(),
                NULL,
                font_weight,
                font_style,
                font_stretch,
                font_size,
                local_name.c_str(),
                &pFormat
            );

            if (pFormat == nullptr) return hr;

            hr = DirectX::pDWriteFactory->CreateTextLayout(
                content.c_str(),
                (UINT32)content.size(),
                pFormat,
                layout_size.width,
                layout_size.height,
                &pLayout
            ); if (FAILED(hr)) return hr;

            return hr;
        }

        // Initialize Format and Layout objects by default properties.
        HRESULT TextFormat::Initialize() {
            HRESULT hr = S_OK;
            WCHAR local_name[LOCALE_NAME_MAX_LENGTH]; GetSystemDefaultLocaleName(local_name, LOCALE_NAME_MAX_LENGTH); // ?
            hr = _update(
                DWRITE_FONT_WEIGHT_NORMAL,
                DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL,
                local_name,
                L"",
                L"Microsoft YaHei",
                32,
                WindowX::Prop::Size
            );
            return hr;
        }

        std::wstring TextFormat::GetContent() {
            return s_content;
        };

        std::wstring TextFormat::GetLocalName() {
            return s_local_name;
        }

        std::wstring TextFormat::GetFontFamilyName() {
            return s_font_family_name;
        }

        Type::SIZE TextFormat::GetLayoutSize() {
            return s_layout_size;
        }

        // Set new contents of Layout object to render.
        HRESULT TextFormat::SetContent(std::wstring new_content) {
            HRESULT hr = _update(
                pFormat->GetFontWeight(),
                pFormat->GetFontStyle(),
                pFormat->GetFontStretch(),
                GetLocalName(),
                new_content,    // the only one parameter to be updated
                GetFontFamilyName(),
                pFormat->GetFontSize(),
                s_layout_size
            );
            return hr;
        }

        HRESULT TextFormat::SetLayoutSize(Type::SIZE new_layout_size) {
            HRESULT hr = _update(
                pFormat->GetFontWeight(),
                pFormat->GetFontStyle(),
                pFormat->GetFontStretch(),
                GetLocalName(),
                s_content,
                GetFontFamilyName(),
                pFormat->GetFontSize(),
                new_layout_size
            );
            return hr;
        }

    }

}
