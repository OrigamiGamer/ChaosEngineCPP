#pragma once

#include <chrono>
#include <vector>

namespace ChaosEngine {
	// Get the current system time(microseconds).
	inline unsigned long long get_system_time();

	class Window;
	
	typedef void (*ON_UPDATE)();
	typedef void (*ON_RENDER)();
	struct INITIAL_ENGINE_PROPERTY {
		Window* window = nullptr;
		ON_UPDATE on_update = nullptr;
		ON_RENDER on_render = nullptr;
		// Units: milliseconds
		std::chrono::milliseconds interval_game_update = std::chrono::milliseconds(1000 / 60);
		// Units: milliseconds
		std::chrono::milliseconds interval_game_render = std::chrono::milliseconds(1000 / 60);
		// Units: milliseconds
		std::chrono::milliseconds interval_window_update = std::chrono::milliseconds(1000 / 60);
	};
	class Engine;
}

#include "Common_PhysicsEngine.h"