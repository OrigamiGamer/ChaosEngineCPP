#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace CompList {

		class ExampleComp : public Model::CompModel {
		private:

		public:
			ExampleComp();

			void Init();
			void Update();
			void Release();

			void Create();

		};

	}

}
