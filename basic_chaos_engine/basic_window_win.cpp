#pragma once

#include "basic_window_win.h"

namespace basic_chaos_engine {
	bool basic_window_win::create(INIT_WND_PROP_WIN& init_wnd_prop) {
		// LPWSTR cls_name = L"chaos_engine_window";
		std::wstring cls_name = L"chaos_engine_window";
		WNDCLASSEXW wndcls{};
		wndcls.cbSize = sizeof(wndcls);
		wndcls.lpfnWndProc = &__global_wnd_proc;
		wndcls.lpszClassName = cls_name.c_str();
		wndcls.hInstance = GetModuleHandleW(NULL);
		wndcls.style = CS_HREDRAW | CS_VREDRAW;
		//wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
		if (RegisterClassExW(&wndcls) == NULL) return false;

		__hwnd = CreateWindowExW(
			NULL,
			cls_name.c_str(),
			init_wnd_prop.title.c_str(),
			init_wnd_prop.style,
			init_wnd_prop.x, init_wnd_prop.y,
			init_wnd_prop.width, init_wnd_prop.height,
			init_wnd_prop.hwnd_parent,
			NULL,
			NULL,
			NULL
		); if (__hwnd == NULL) return false;
		//ShowWindow(__hwnd, SW_SHOW);
		UpdateWindow(__hwnd);
		__map_init_wnd_prop.insert({ __hwnd, init_wnd_prop });
		SendMessage(__hwnd, WM_GAME_INIT, 0, 0);
		return true;
	}
	DWORD basic_window_win::tranform_style(std::bitset<32> style) {
		// !! The order of this map is connected to the order of the basic_window::WINDOW_STYLE !!
		const std::array<DWORD, 32> style_map = {
			WS_VISIBLE,
			WS_OVERLAPPEDWINDOW,
		};
		DWORD _win32_wnd_style = NULL;
		for (size_t i = 0; i < style.size(); i++) if (style[i]) _win32_wnd_style |= style_map[i];
		return _win32_wnd_style;
	}
	HWND basic_window_win::get_handle() const {
		return __hwnd;
	}
	bool basic_window_win::update() {
		MSG msg{};
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			return true;
		}
		return false;
	}


	// Start a thread for Window Message Loop on Win32.
	void start_window_msg_loop() {
		MSG msg{};
		while (GetMessage(&msg, NULL, 0, 0) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// Window Process.
	LRESULT CALLBACK __global_wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		switch (msg) {
		case WM_CLOSE:
			if (__map_init_wnd_prop.at(hwnd).on_exit != nullptr)
				if (__map_init_wnd_prop.at(hwnd).on_exit())
					DestroyWindow(hwnd);
			return 0;
		case WM_DESTROY:
			OutputDebugStringW(L"window process was destroyed\n");
			PostQuitMessage(0);
			return 0;
		default:
			if (msg == WM_GAME_INIT) {
				if (__map_init_wnd_prop.at(hwnd).on_init != nullptr) {
					// win32 thread problem !!!!!
					//if (*__init_wnd_prop.out_pp_hwnd != nullptr) **__init_wnd_prop.out_pp_hwnd = hwnd;
					if (!__map_init_wnd_prop.at(hwnd).on_init()) DestroyWindow(hwnd);
				}
			}
			break;
		}
		if (__map_init_wnd_prop.size() > 0)
			if (__map_init_wnd_prop.at(hwnd).wnd_proc != nullptr)
				return __map_init_wnd_prop.at(hwnd).wnd_proc(hwnd, msg, wparam, lparam);
		return DefWindowProcW(hwnd, msg, wparam, lparam);
	}
}