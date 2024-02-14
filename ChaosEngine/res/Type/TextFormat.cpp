#pragma once
#include "_list.h"

namespace ChaosEngine {

    namespace Type {

        TextFormat::TextFormat() {
            pFormat = nullptr;
            pLayout = nullptr;
            Initialize();
        }

        HRESULT TextFormat::Initialize() {
            Release();

            HRESULT hr = NULL;

            DWRITE_FONT_WEIGHT font_weight = DWRITE_FONT_WEIGHT_NORMAL;
            DWRITE_FONT_STYLE font_style = DWRITE_FONT_STYLE_NORMAL;
            DWRITE_FONT_STRETCH font_stretch = DWRITE_FONT_STRETCH_NORMAL;
            WCHAR local_name[LOCALE_NAME_MAX_LENGTH]; GetSystemDefaultLocaleName(local_name, LOCALE_NAME_MAX_LENGTH); // ?

            std::wstring content = L"";
            std::wstring fontFamilyName = L"Microsoft YaHei";   // BEDROCK
            FLOAT fontSize = 32;
            Type::SIZE layoutSize = Property::Window::Size;

            hr = WindowX::pDWriteFactory->CreateTextFormat(
                fontFamilyName.c_str(),
                NULL,
                font_weight,
                font_style,
                font_stretch,
                fontSize,
                local_name,
                &pFormat
            );

            if (pFormat) {
                hr = WindowX::pDWriteFactory->CreateTextLayout(
                    content.c_str(),
                    (UINT32)content.size(),
                    pFormat,
                    layoutSize.width,
                    layoutSize.height,
                    &pLayout
                ); if (FAILED(hr)) return hr;
            }
            else return hr;
            return hr;
        }

        void TextFormat::Release() {
            SafeRelease(&pFormat);
            SafeRelease(&pLayout);
        }

        HRESULT TextFormat::_update(
            DWRITE_FONT_WEIGHT font_weight = DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE font_style = DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH font_stretch = DWRITE_FONT_STRETCH_NORMAL,
            WCHAR* local_name
        ) {

            Release();

            HRESULT hr = NULL;

            DWRITE_FONT_WEIGHT font_weight = DWRITE_FONT_WEIGHT_NORMAL;
            DWRITE_FONT_STYLE font_style = DWRITE_FONT_STYLE_NORMAL;
            DWRITE_FONT_STRETCH font_stretch = DWRITE_FONT_STRETCH_NORMAL;
            WCHAR local_name[LOCALE_NAME_MAX_LENGTH]; GetSystemDefaultLocaleName(local_name, ); // ?
            

            std::wstring content = L"";
            std::wstring fontFamilyName = L"Microsoft YaHei";   // BEDROCK
            FLOAT fontSize = 32;
            Type::SIZE layoutSize = Property::Window::Size;

            hr = WindowX::pDWriteFactory->CreateTextFormat(
                fontFamilyName.c_str(),
                NULL,
                font_weight,
                font_style,
                font_stretch,
                fontSize,
                local_name,
                &pFormat
            );

            if (pFormat) {
                hr = WindowX::pDWriteFactory->CreateTextLayout(
                    content.c_str(),
                    (UINT32)content.size(),
                    pFormat,
                    layoutSize.width,
                    layoutSize.height,
                    &pLayout
                ); if (FAILED(hr)) return hr;
            }
            else return hr;
            return hr;
        }

        HRESULT TextFormat::SetContent(std::wstring new_content) {
            HRESULT hr = NULL;

            DWRITE_FONT_WEIGHT font_weight = DWRITE_FONT_WEIGHT_NORMAL;
            DWRITE_FONT_STYLE font_style = DWRITE_FONT_STYLE_NORMAL;
            DWRITE_FONT_STRETCH font_stretch = DWRITE_FONT_STRETCH_NORMAL;
            WCHAR local_name[LOCALE_NAME_MAX_LENGTH]; GetSystemDefaultLocaleName(local_name, LOCALE_NAME_MAX_LENGTH); // ?

            std::wstring content = new_content;
            const UINT32 _len_fontFamilyName= pFormat->GetFontFamilyNameLength();
            WCHAR* fontFamilyName = nullptr; pFormat->GetFontFamilyName(fontFamilyName, _len_fontFamilyName);
            FLOAT fontSize = pFormat->GetFontSize();
            Type::SIZE layoutSize = ;

            Release();

            hr = WindowX::pDWriteFactory->CreateTextFormat(
                fontFamilyName,
                NULL,
                font_weight,
                font_style,
                font_stretch,
                fontSize,
                local_name,
                &pFormat
            );

            if (pFormat) {
                hr = WindowX::pDWriteFactory->CreateTextLayout(
                    content.c_str(),
                    (UINT32)content.size(),
                    pFormat,
                    layoutSize.width,
                    layoutSize.height,
                    &pLayout
                ); if (FAILED(hr)) return hr;
            }
            else return hr;
            return hr;
        }

        

        /*void Set() {
            const DWRITE_TRIMMING dw_trimming;
            IDWriteInlineObject* w = nullptr;
            Format->SetTrimming(&dw_trimming, w);

        }*/

    }

}
