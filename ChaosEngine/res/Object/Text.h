#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace ObjectList {

		class Text : public Model::ObjectModel {
		private:
			std::wstring content;
			Type::TextFormat textFormat;
			Type::POS* pMousePos;

		public:
			Text();
			void Init();
			void Update();
			void Render();
			void Release();

			void Create();
			void SetContent(std::wstring new_content);
			BOOL HitTest();
			BOOL IsInside();

		};

	}

}
