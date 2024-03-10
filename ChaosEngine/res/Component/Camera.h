#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace CompList {

		class Camera : public Model::CompModel {
		private:

		public:
			Type::POS viewPos;
			Type::SIZE viewSize;
			Type::SCALE viewScale;

			Camera();
			void Init();
			void Update();
			void Release();

			void Create();

		};

	}

}
