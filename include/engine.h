#pragma once

#include "chaos_engine.h"

namespace ChaosEngine {
	class Engine {
	public:
		Window* window;
	public:
		inline bool initialize(Window& new_window);
		
	};

}