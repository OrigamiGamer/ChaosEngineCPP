#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace Type {

		Texture::Texture() {
			pD2DBitmap = NULL;
		}

		void Texture::Init() {

		}

		void Texture::Release() {
			SafeRelease(&pD2DBitmap);
		}

		Type::SIZE Texture::GetSize() {
			D2D1_SIZE_U size{};
			if (pD2DBitmap) size = pD2DBitmap->GetPixelSize();
			return Type::SIZE((float)size.width, (float)size.height);
		}

	}

}
