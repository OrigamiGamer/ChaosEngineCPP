#pragma once

#include <Windows.h>

#include "basic_common.h"

namespace basic_chaos_engine {
	// Win32
	class basic_window_win {
	public:
		// Initial property of new window
		struct INIT_WND_PROP_WIN {
			std::wstring title = L"None Window";
			int x = CW_USEDEFAULT;
			int y = CW_USEDEFAULT;
			int width = CW_USEDEFAULT;
			int height = CW_USEDEFAULT;
			DWORD style = WS_OVERLAPPEDWINDOW;
			HWND hwnd_parent = NULL;
			HINSTANCE hInstance = NULL;
			ON_INIT on_init = nullptr;
			ON_EXIT on_exit = nullptr;
			WNDPROC wnd_proc = nullptr;
			//HWND** out_pp_hwnd = nullptr;
		};

	private:
		HANDLE_WINDOW __hwnd;
	public:
		// Create a Win32 window, start its Window Message Loop and wait for it to be ended.
		bool create(INIT_WND_PROP_WIN& init_wnd_prop);
		// Transform to Win32 window style.
		DWORD tranform_style(std::bitset<32> style);
		// Get the handle of the Win32 window.
		HWND get_handle() const;
		// Update the Win32 window by processing its Window Message Loop.
		bool update();
	};

	std::unordered_map<HANDLE_WINDOW, basic_window_win::INIT_WND_PROP_WIN> __map_init_wnd_prop;

	void start_window_msg_loop();
	LRESULT CALLBACK __global_wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
}