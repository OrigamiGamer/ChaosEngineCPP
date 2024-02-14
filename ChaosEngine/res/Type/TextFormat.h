#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace Type {

        class TextFormat : public Model::PropertyModel {
        public:
            Type::SIZE layoutSize;
            // directly call these two interfaces
            IDWriteTextFormat* pFormat;
            IDWriteTextLayout* pLayout;

        private:
            HRESULT _update(
                DWRITE_FONT_WEIGHT font_weight,
                DWRITE_FONT_STYLE font_style,
                DWRITE_FONT_STRETCH font_stretch,
                WCHAR* local_name,
                std::wstring content,
                std::wstring font_family_name,
                FLOAT font_size,
                Type::SIZE layout_size
            );

        public:
            TextFormat();
            void Init();
            void Release();
            HRESULT Initialize();
            HRESULT SetContent(std::wstring new_content);

        };

	}

}
