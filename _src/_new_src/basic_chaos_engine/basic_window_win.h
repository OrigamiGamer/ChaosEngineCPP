#pragma once

#include <Windows.h>

#include "basic_common.h"

namespace basic_chaos_engine {
	// Win32
	namespace basic_window_win {
		// Initial property of new window
		struct INIT_WND_PROP_WIN;
		struct INIT_WND_PROP_WIN {
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
			WNDPROC __global_wnd_proc = nullptr;
			HWND** out_pp_hwnd = nullptr;
		} __init_wnd_prop{};

		bool create(INIT_WND_PROP_WIN& init_wnd_prop);
		LRESULT CALLBACK __global_wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		DWORD tranform_style(std::bitset<32> style);
		HWND get_handle_window();
	}
}