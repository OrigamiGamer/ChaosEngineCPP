#pragma once
#include "TypeList.h"

namespace ChaosEngine {

	namespace Type {

		class Texture {
		public:
			ID2D1Bitmap* pD2DBitmap = NULL;

			Type::SIZE GetSize() {
				D2D1_SIZE_U size{};
				if (pD2DBitmap) size = pD2DBitmap->GetPixelSize();
				return Type::SIZE((float)size.width, (float)size.height);
			};

		};

	}

}
