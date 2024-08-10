#pragma once

#include "chaos_engine.h"

namespace ChaosEngine {
	class Engine {
	private:
		bool running; // default to false
	public:
		basic_chaos_engine::basic_graphic graphic;
		INITIAL_ENGINE_PROPERTY properties;
	public:
		Engine();
		inline bool Initialize(INITIAL_ENGINE_PROPERTY& initial_property);
		bool Run();
		bool Shutdown();
	};
}