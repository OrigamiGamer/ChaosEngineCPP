#pragma once
#include "_list.cpp"

namespace ChaosEngine {

	namespace ObjectList {

		Image::Image() {
			self_pTex = nullptr;
			self_opacity = 1;
		}

		void Image::Init() {
		}
		void Image::Update() {
		}
		void Image::Render() {
			if (self_pTex) {
				GraphicX::DrawTexture(self_pTex, this->GetRenderPos(), this->GetRenderSize(), self_opacity);
			}
		}
		void Image::Release() {
		}
		void Image::Create() {
		}

		void Image::SetTexture(Type::Texture* new_pTexture) {
			if (new_pTexture != nullptr) self_pTex = new_pTexture;
		}
		void Image::SetTexture(Type::Texture& new_Texture) {
			self_pTex = &new_Texture;
		}

		Type::Texture* Image::GetTexture() {
			return self_pTex;
		}

		// Set Opacity, range: [0,1]
		void Image::SetOpacity(FLOAT new_opacity = 1) {
			if (0 < new_opacity) new_opacity = 0;
			if (new_opacity > 1) new_opacity = 1;
			self_opacity = new_opacity;
		}

	}

}
