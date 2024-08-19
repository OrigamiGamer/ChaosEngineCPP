#pragma once

#include "Window.h"

namespace ChaosEngine {
	inline void Window::Initialize(basic_chaos_engine::basic_window::INITIAL_WINDOW_PROPERTY init_wnd_prop) {
		_basic_window.create(init_wnd_prop);
	}
	inline basic_type::vec2<int> Window::GetSize() const {
		return _basic_window.get_size();
	}
	inline basic_type::vec2<int> Window::GetPos() const {
		return _basic_window.get_pos();
	}
	inline basic_chaos_engine::type::HANDLE_WINDOW Window::GetHandle() const {
		return _basic_window.get_handle();
	}
	inline bool Window::Update() {
		return _basic_window.update();
	}
}