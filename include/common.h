#pragma once

#include "basic_type.h"

namespace ChaosEngine {
	// Get the current system time(microseconds).
	unsigned long long get_system_time();

	class Window;

	typedef void (*ON_UPDATE)();
	typedef void (*ON_RENDER)();

	struct INITIAL_ENGINE_PROPERTY {
		Window* window = nullptr;
		ON_UPDATE on_update = nullptr;
		ON_RENDER on_render = nullptr;
		std::chrono::milliseconds interval_game_update = std::chrono::milliseconds(1000 / 60);
		std::chrono::milliseconds interval_game_render = std::chrono::milliseconds(1000 / 60);
		std::chrono::milliseconds interval_window_update = std::chrono::milliseconds(1000 / 60);
	};
	class Engine;
}