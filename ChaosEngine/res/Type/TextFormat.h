#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace Type {

		class TextFormat {
		public:
            // directly call these two
			IDWriteTextFormat* pFormat;
            IDWriteTextLayout* pLayout;

        public:
            TextFormat();
            HRESULT Initialize();
			void Release();
			HRESULT _update();
			HRESULT TextFormat::SetContent(std::wstring new_content);

		};

	}

}
