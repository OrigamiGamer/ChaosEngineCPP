#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace ObjectList {

		Image::Image() {
			self_pTex = nullptr;
			self_opacity = 1;
		};

		void Image::Init() { };
		void Image::Update() { };
		void Image::Render() {
			if (self_pTex) {
				GraphicX::DrawTexture(self_pTex, this->pos, this->size, self_opacity);
			}
		};
		void Image::Release() { };
		void Image::Create() { };

		void Image::SetTexture(Type::Texture*& lpTexture) {
			self_pTex = lpTexture;
		};
		Type::Texture* Image::GetTexture() {
			return self_pTex;
		};

		// Set Opacity, range: [0,1]
		void Image::SetOpacity(FLOAT new_opacity = 1) {
			if (0 < new_opacity) new_opacity = 0;
			if (new_opacity > 1) new_opacity = 1;
			self_opacity = new_opacity;
		};

	}

}
