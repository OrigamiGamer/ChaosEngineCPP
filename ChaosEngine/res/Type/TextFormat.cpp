#pragma once
#include "_list.h"

namespace ChaosEngine {

    namespace Type {

        TextFormat::TextFormat() {
            layoutSize = Property::Window::Size;
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
            WCHAR* local_name,
            std::wstring content,
            std::wstring font_family_name,
            FLOAT font_size,
            Type::SIZE layout_size
        ) {
            Release();
            HRESULT hr = NULL;

            hr = WindowX::pDWriteFactory->CreateTextFormat(
                font_family_name.c_str(),
                NULL,
                font_weight,
                font_style,
                font_stretch,
                font_size,
                local_name,
                &pFormat
            );

            if (pFormat) {
                hr = WindowX::pDWriteFactory->CreateTextLayout(
                    content.c_str(),
                    (UINT32)content.size(),
                    pFormat,
                    layout_size.width,
                    layout_size.height,
                    &pLayout
                ); if (FAILED(hr)) return hr;
            }
            else return hr;
            return hr;
        }

        // Initialize Format and Layout objects by default properties.
        HRESULT TextFormat::Initialize() {
            HRESULT hr = NULL;

            WCHAR local_name[LOCALE_NAME_MAX_LENGTH]; GetSystemDefaultLocaleName(local_name, LOCALE_NAME_MAX_LENGTH); // ?
            hr = _update(
                DWRITE_FONT_WEIGHT_NORMAL,
                DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL,
                local_name,
                L"",
                L"Microsoft YaHei",
                32,
                layoutSize  // Property::Window::Size
            );

            return hr;
        }

        // Set new contents of Layout object to render.
        HRESULT TextFormat::SetContent(std::wstring new_content) {
            UINT32 len = 0;

            std::unique_ptr<WCHAR[]> local_name; len = pFormat->GetLocaleNameLength();
            local_name.reset(new WCHAR[len]); pFormat->GetLocaleName(local_name.get(), len);

            std::unique_ptr<WCHAR[]> font_family_name; len = pFormat->GetFontFamilyNameLength();
            font_family_name.reset(new WCHAR[len]); pFormat->GetFontFamilyName(font_family_name.get(), len);

            HRESULT hr = _update(
                pFormat->GetFontWeight(),
                pFormat->GetFontStyle(),
                pFormat->GetFontStretch(),
                local_name.get(),
                new_content,    // the only one parameter to be updated
                font_family_name.get(),
                pFormat->GetFontSize(),
                layoutSize
            );

            return hr;
        }

        

        /*void Set() {
            const DWRITE_TRIMMING dw_trimming;
            IDWriteInlineObject* w = nullptr;
            Format->SetTrimming(&dw_trimming, w);

        }*/

    }

}
