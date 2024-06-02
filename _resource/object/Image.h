#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace ObjectList {

		class Image : public Model::ObjectModel {
		private:
			Type::Texture* self_pTex;
			FLOAT self_opacity;

		public:
			Image();

			void Init();
			void Update();
			void Render();
			void Release();

			void Create();
			void SetTexture(Type::Texture* pTexture);
			void SetTexture(Type::Texture& new_Texture);
			Type::Texture* GetTexture();
			void SetOpacity(FLOAT new_opacity);

		};

	}

}
