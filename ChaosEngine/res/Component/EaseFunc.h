#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace CompList {

		class EaseFunc : public Model::CompModel {
		private:
			double index = 1;	// linear
			
		public:
			EaseFunc();

			void Init();
			void Update();
			void Release();

			void Create();

		};

	}

}
