#pragma once

#include "basic_window.h"

#ifdef _WIN32
namespace basic_chaos_engine {
	namespace basic_window {
		bool create_window(INITIAL_WINDOW_PROPERTY init_wnd_prop) {
			basic_window_win::INITIAL_WINDOW_PROPERTY _wnd_prop{};
			_wnd_prop.hInstance = NULL;
			_wnd_prop.hwnd_parent = NULL;
			_wnd_prop.title = init_wnd_prop.title;
			_wnd_prop.on_init = init_wnd_prop.on_init;
			_wnd_prop.on_exit = init_wnd_prop.on_exit;
			if (init_wnd_prop.style != NULL) 
				_wnd_prop.style = basic_window_win::tranform_style(init_wnd_prop.style);
			HWND hwnd = basic_window_win::create_window(_wnd_prop);
			if (hwnd == NULL) return false;
			return true;
		}
	}
}
#elif __linux__
#endif