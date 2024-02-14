#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace Type {

		class Texture {
		public:
			ID2D1Bitmap* pD2DBitmap;

			Texture();
			Type::SIZE GetSize();

		};

	}

}
