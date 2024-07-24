#pragma once

#include <Windows.h>

#include "basic_common.h"

namespace basic_chaos_engine {
	namespace basic_window_win {
		// Initial property of new window
		struct INITIAL_WINDOW_PROPERTY;
		struct INITIAL_WINDOW_PROPERTY {
			std::wstring title = L"None Window";
			int x = CW_USEDEFAULT;
			int y = CW_USEDEFAULT;
			int width = CW_USEDEFAULT;
			int height = CW_USEDEFAULT;
			DWORD style = WS_OVERLAPPEDWINDOW;
			HWND hwnd_parent = NULL;
			HINSTANCE hInstance = NULL;
			basic_window::ON_INIT on_init = nullptr;
			basic_window::ON_EXIT on_exit = nullptr;
			WNDPROC wnd_proc = nullptr;
		};
		INITIAL_WINDOW_PROPERTY __init_wnd_prop{};
		HWND create_window(INITIAL_WINDOW_PROPERTY init_wnd_prop);
		LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		DWORD tranform_style(std::bitset<32> style);
	}
}