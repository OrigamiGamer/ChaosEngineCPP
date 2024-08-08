#pragma once

#include "basic_window.h"

#ifdef _WIN32
namespace basic_chaos_engine {
	bool basic_window::create(INITIAL_WINDOW_PROPERTY& init_wnd_prop) {
		// tranform window properties to Win32
		basic_window_win::INIT_WND_PROP_WIN _wnd_prop{};
		_wnd_prop.hInstance = NULL;
		_wnd_prop.hwnd_parent = NULL;
		//_wnd_prop.out_pp_hwnd = &init_wnd_prop.out_p_hwnd;	// ?
		_wnd_prop.title = init_wnd_prop.title;
		if (init_wnd_prop.on_init != nullptr) _wnd_prop.on_init = init_wnd_prop.on_init;
		if (init_wnd_prop.on_exit != nullptr) _wnd_prop.on_exit = init_wnd_prop.on_exit;
		if (init_wnd_prop.x != Const::DEFAULT) _wnd_prop.x = init_wnd_prop.x;
		if (init_wnd_prop.y != Const::DEFAULT) _wnd_prop.y = init_wnd_prop.y;
		if (init_wnd_prop.width != Const::DEFAULT) _wnd_prop.width = init_wnd_prop.width;
		if (init_wnd_prop.height != Const::DEFAULT) _wnd_prop.height = init_wnd_prop.height;
		if (init_wnd_prop.style != NULL) _wnd_prop.style = _window_win.tranform_style(init_wnd_prop.style);
		return _window_win.create(_wnd_prop);
	}
	inline HANDLE_WINDOW basic_window::get_handle() const {
		//if (__init_wnd_prop.out_p_hwnd != nullptr) return *__init_wnd_prop.out_p_hwnd;
		return _window_win.get_handle();
	}
	inline basic_type::vec2<int> basic_window::get_size() const {
		RECT rect{}; GetWindowRect(get_handle(), &rect);
		return basic_type::vec2<int>{rect.right - rect.left, rect.bottom - rect.top};
	}
	inline bool basic_window::update() {
		return _window_win.update();
	}
}
#elif __linux__
#endif