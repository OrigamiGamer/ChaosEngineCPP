#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace ObjectList {

		class Text : public Model::ObjectModel {
		private:
			Type::POS* s_pCursorPos;
		public:
			Type::COLOR color = { 0, 0 };
			Type::TextFormat textFormat;
		public:
			Text();
			void Init();
			void Update();
			void Render();
			void Release();

			void Create();
			BOOL OnHover();
			BOOL IsInside();

		};

	}

}
