#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace Type {

		class Texture : public Model::PropertyModel {
		public:
			ID2D1Bitmap* pD2DBitmap;

			Texture();
			void Init();
			void Release();
			Type::SIZE GetSize() const;

		};

	}

}
