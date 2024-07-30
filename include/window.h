#pragma once

#include "basic_window.h"

namespace ChaosEngine {
	class Window {
	public:
		basic_core::basic_window::HANDLE_WINDOW hwnd;
	public:
		inline basic_core::basic_window::HANDLE_WINDOW initialize(basic_core::basic_window::INITIAL_WINDOW_PROPERTY init_wnd_prop);
		inline basic_type::vec2<int> get_size() const;
	};
}
