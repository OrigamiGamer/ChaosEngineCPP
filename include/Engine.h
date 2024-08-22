#pragma once

#include "chaos_engine.h"

namespace ChaosEngine {
	class Engine {
	private:
		bool running; // default to false
	public:
		basic_chaos_engine::basic_graphic graphic;
		INITIAL_ENGINE_PROPERTY properties;
		// Units: milliseconds
		unsigned long long last_time_update, last_time_render, last_time_window;
		// Units: milliseconds
		unsigned long long delta_time_update, delta_time_render, delta_time_window;
		unsigned long long fps;

	public:
		Engine();
		inline bool Initialize(INITIAL_ENGINE_PROPERTY& initial_property);
		// Start a Game Loop.
		bool Run();
		// Shutdown the game loop and release all resources.
		bool Shutdown();
	private:
		void EngineUpdate();
		void EngineRender();
	};
}