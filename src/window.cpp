#pragma once

#include "Window.h"

namespace ChaosEngine {
	bool Window::initialize(basic_window::INITIAL_WINDOW_PROPERTY init_win_prop) {
		bool _state = basic_window::create_window(init_win_prop);
		vec_window.push_back(this);
		return _state;
	}
}