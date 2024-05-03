#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace ObjectList {

		class Text : public Model::ObjectModel {
		private:
			Type::POS* s_pCursorPos = nullptr;
		public:
			Type::COLOR color = { D2D1::ColorF::LightPink, 1 };
			Type::TextFormat textFormat;
		public:
			Text();
			void Init();
			void Update();
			void Render();
			void Release();

			void Create();
			BOOL OnHover();

		};

	}

}
