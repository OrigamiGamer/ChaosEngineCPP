#pragma once

#include "Window.h"

namespace ChaosEngine {
	inline void Window::Initialize(basic_chaos_engine::basic_window::INITIAL_WINDOW_PROPERTY init_wnd_prop) {
		// TODO: start a thread to create window
		basic_chaos_engine::basic_window::create(init_wnd_prop);
	}
	inline basic_type::vec2<int> Window::GetSize() const {
		return basic_chaos_engine::basic_window::get_window_size(hwnd);
	}
}