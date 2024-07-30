#pragma once

#include "Window.h"

namespace ChaosEngine {
	inline basic_core::basic_window::HANDLE_WINDOW Window::initialize(basic_core::basic_window::INITIAL_WINDOW_PROPERTY init_wnd_prop) {
		
		basic_core::basic_window::create_window(init_wnd_prop);
		return *init_wnd_prop.out_p_hwnd;
	}
	inline basic_type::vec2<int> Window::get_size() const {
		return basic_core::basic_window::get_window_size(hwnd);
	}
}