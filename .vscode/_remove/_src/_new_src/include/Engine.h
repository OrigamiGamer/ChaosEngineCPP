#pragma once

#include "chaos_engine.h"

namespace ChaosEngine {
	class Engine {
	public:
		Window* window;
	public:
		inline bool Initialize(Window& new_window);
		
	};

}