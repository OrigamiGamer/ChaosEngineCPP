#pragma once

#include "basic_window.h"

namespace ChaosEngine {
	class Window {
	public:
		basic_chaos_engine::basic_window _basic_window;
	private:
		basic_chaos_engine::type::HANDLE_WINDOW _hwnd;
	public:
		inline void Initialize(basic_chaos_engine::basic_window::INITIAL_WINDOW_PROPERTY init_wnd_prop);
		inline basic_type::vec2<int> GetSize() const;
		inline basic_type::vec2<int> GetPos() const;
		inline basic_chaos_engine::type::HANDLE_WINDOW GetHandle() const;
		inline bool Update();
	};
}