#pragma once
#include "ObjectList.h"

namespace ChaosEngine {

	namespace ObjectList {

		Image::Image() {
			self_pTex = NULL;
			self_opacity = 1;
		};

		void Image::Init() {
		};
		void Image::Update() {
		};
		void Image::Render() {
			if (self_pTex) {
				Type::POS pos = this->GetPos();
				Type::SIZE size = this->GetSize();
				WindowX::pHwndRenderTarget->DrawBitmap(
					self_pTex->pD2DBitmap,
					D2D1::RectF(pos.x, pos.y, pos.x + size.width, pos.y = size.height),
					self_opacity,
					D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
				);
			}
		};
		void Image::Release() {
		};

		void Image::Create() {

		};

		// Set lpTexture
		void Image::SetTexture(Type::Texture* lpTexture) {
			if (lpTexture) self_pTex = lpTexture;
		};

		// Get lpTexture
		Type::Texture* Image::GetTexture() {
			return self_pTex;
		};

	}

}
