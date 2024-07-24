#pragma once

#include "basic_window.h"

namespace ChaosEngine {
	using namespace basic_chaos_engine;
	class Window;
	class Window {
	public:
		bool initialize(basic_window::INITIAL_WINDOW_PROPERTY init_win_prop);
	};
	std::vector<Window*> vec_window;
}
