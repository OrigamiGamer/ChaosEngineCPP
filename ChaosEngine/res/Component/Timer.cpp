#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {
	
	class Timer : public Model::CompModel {
	public:
		int Init() { return 0; };
		int Update() { return 0; };
		int Render() { return 0; };
		int Release() { return 0; };	// try to make the objects into the scene

	};

}
