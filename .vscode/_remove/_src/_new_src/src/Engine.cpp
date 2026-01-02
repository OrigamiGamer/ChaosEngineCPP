#pragma once

#include "engine.h"

namespace ChaosEngine {
	inline bool Engine::Initialize(Window& new_window) {
		window = &new_window;
		basic_chaos_engine::basic_Graphics::initialize_Graphics(window->hwnd);
		return true;
	}
}