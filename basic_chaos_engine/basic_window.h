#pragma once

#include "basic_common.h"

#ifdef _WIN32
#include "basic_window_win.h"
#elif __linux__
#endif

namespace basic_chaos_engine {
	class basic_window {
	public:
		struct INITIAL_WINDOW_PROPERTY {
			std::wstring title = L"game window";
			ON_INIT on_init = nullptr;
			ON_EXIT on_exit = nullptr;
			int x = Const::DEFAULT, y = Const::DEFAULT, width = Const::DEFAULT, height = Const::DEFAULT;
			std::bitset<32> style;
			//HANDLE_WINDOW* out_p_hwnd;
		};

	public:
		basic_window_win _window_win;

		// Create a new window.
		bool create(INITIAL_WINDOW_PROPERTY& init_wnd_prop);
		// Get window handle.
		inline HANDLE_WINDOW get_handle() const;
		// Get size of the window.
		inline basic_type::vec2<int> get_size() const;
		// Get position of the window.
		inline basic_type::vec2<int> get_pos() const;
		// Update the window.
		inline bool update();
	};
}