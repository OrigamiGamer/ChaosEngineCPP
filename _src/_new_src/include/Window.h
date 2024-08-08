#pragma once

#include "basic_window.h"

namespace ChaosEngine {
	class Window {
	public:
		basic_chaos_engine::basic_window::HANDLE_WINDOW hwnd;
	public:
		inline void Initialize(basic_chaos_engine::basic_window::INITIAL_WINDOW_PROPERTY init_wnd_prop);
		inline basic_type::vec2<int> GetSize() const;
	};
}