#pragma once
#include "ModelList.h"

namespace ChaosEngine {

	namespace Model {

		class CompModel {
		public:

			virtual void Init() {};
			virtual void Update() {};
			virtual void Render() {};
			virtual void Release() {};

		};
		  
	}

}
