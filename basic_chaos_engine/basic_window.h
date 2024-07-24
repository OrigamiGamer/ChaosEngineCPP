#pragma once

#include "basic_common.h"

#ifdef _WIN32

#include "basic_window_win.h"

// common standards
namespace basic_chaos_engine {
	namespace basic_window {
		struct INITIAL_WINDOW_PROPERTY;
		struct INITIAL_WINDOW_PROPERTY {
			std::wstring title = L"game window";
			ON_INIT on_init = nullptr;
			ON_EXIT on_exit = nullptr;
			int x, y, width, height;
			std::bitset<32> style;
		};
		bool create_window(INITIAL_WINDOW_PROPERTY init_wnd_prop);
	}
}

#elif __linux__
#endif
