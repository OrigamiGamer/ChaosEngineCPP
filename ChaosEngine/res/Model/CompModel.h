#pragma once
#include "ModelList.h"

namespace ChaosEngine {

	namespace Model {

		class CompModel {
		public:

			virtual int Init() { return -1; };
			virtual int Update() { return -1; };
			virtual int Render() { return -1; };
			virtual int Release() { return -1; };

		};

	}

}
