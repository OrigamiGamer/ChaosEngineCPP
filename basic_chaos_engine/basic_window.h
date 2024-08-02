#pragma once

#include "basic_common.h"

#ifdef _WIN32
#include "basic_window_win.h"

namespace basic_core {
	namespace basic_window {
		struct INITIAL_WINDOW_PROPERTY {
			std::wstring title = L"game window";
			ON_INIT on_init = nullptr;
			ON_EXIT on_exit = nullptr;
			int x = Const::DEFAULT, y = Const::DEFAULT, width = Const::DEFAULT, height = Const::DEFAULT;
			std::bitset<32> style;
			HANDLE_WINDOW* out_p_hwnd;
		};
		bool create_window(INITIAL_WINDOW_PROPERTY& init_wnd_prop);
		inline basic_type::vec2<int> get_window_size(HANDLE_WINDOW hwnd);
	}
}

#elif __linux__
#endif
