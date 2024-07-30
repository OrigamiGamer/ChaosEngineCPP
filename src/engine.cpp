#pragma once

#include "engine.h"

namespace ChaosEngine {
	inline bool Engine::initialize(Window& new_window) {
		window = &new_window;
		return true;
	}
}