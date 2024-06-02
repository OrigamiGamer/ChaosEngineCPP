#pragma once
#include "ResList.h"

namespace ChaosEngine {

	namespace Type {

        class TextFormat : public Model::PropertyModel {
        private:
            std::wstring s_content;
            std::wstring s_local_name;
            std::wstring s_font_family_name;
            Type::SIZE s_layout_size;
        public:
            // directly call these two interfaces
            IDWriteTextFormat* pFormat;
            IDWriteTextLayout* pLayout;

        public:
            TextFormat();
            void Init();
            void Release();
            HRESULT _update(
                DWRITE_FONT_WEIGHT font_weight,
                DWRITE_FONT_STYLE font_style,
                DWRITE_FONT_STRETCH font_stretch,
                std::wstring local_name,
                std::wstring content,
                std::wstring font_family_name,
                FLOAT font_size,
                Type::SIZE layout_size
            );
            HRESULT Initialize();
            std::wstring GetContent();
            std::wstring GetLocalName();
            std::wstring GetFontFamilyName();
            Type::SIZE GetLayoutSize();
            HRESULT SetContent(std::wstring new_content);
            HRESULT SetLayoutSize(Type::SIZE new_layout_size);

        };

	}

}
