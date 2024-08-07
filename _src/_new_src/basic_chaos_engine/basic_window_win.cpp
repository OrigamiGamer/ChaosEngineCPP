#pragma once

#include "basic_window_win.h"

namespace basic_chaos_engine {
	// Win32
	namespace basic_window_win {
		bool create(INIT_WND_PROP_WIN& init_wnd_prop) {
			__init_wnd_prop = init_wnd_prop;

			LPWSTR cls_name = L"chaos_engine_window";
			HWND hwnd = NULL;
			WNDCLASSEXW wndcls{};
			wndcls.cbSize = sizeof(wndcls);
			wndcls.lpfnWndProc = &__global_wnd_proc;
			wndcls.lpszClassName = cls_name;
			wndcls.hInstance = GetModuleHandleW(NULL);
			wndcls.style = CS_HREDRAW | CS_VREDRAW;
			//wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
			if (RegisterClassExW(&wndcls) == NULL) return false;

			hwnd = CreateWindowExW(
				NULL,
				cls_name,
				init_wnd_prop.title.c_str(),
				init_wnd_prop.style,
				init_wnd_prop.x,
				init_wnd_prop.y,
				init_wnd_prop.width,
				init_wnd_prop.height,
				init_wnd_prop.hwnd_parent,
				NULL,
				NULL,
				NULL
			); if (hwnd == NULL) return false;
			//ShowWindow(hwnd, SW_SHOW);
			UpdateWindow(hwnd);

			MSG msg = {};
			while (GetMessage(&msg, NULL, 0, 0) > 0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return true;
		}

		LRESULT CALLBACK __global_wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			switch (msg) {
			case WM_CREATE:
				if (__init_wnd_prop.on_init != nullptr) {
					// win32 thread problem
					if (*__init_wnd_prop.out_pp_hwnd != nullptr) **__init_wnd_prop.out_pp_hwnd = hwnd;
					if (!__init_wnd_prop.on_init()) DestroyWindow(hwnd);
				}
				break;
			case WM_CLOSE:
				if (__init_wnd_prop.on_exit != nullptr)
					if (__init_wnd_prop.on_exit()) DestroyWindow(hwnd);
				return 0;
			case WM_DESTROY:
				OutputDebugStringW(L"window process was destroyed\n");
				PostQuitMessage(0);
				return 0;
			default:
				break;
			}
			if (__init_wnd_prop.__global_wnd_proc != nullptr)
				return __init_wnd_prop.__global_wnd_proc(hwnd, msg, wparam, lparam);
			return DefWindowProcW(hwnd, msg, wparam, lparam);
		}

		DWORD tranform_style(std::bitset<32> style) {
			// !! The order of this map is connected to the order of the basic_window::WINDOW_STYLE !!
			const std::array<DWORD, 32> style_map = {
				WS_VISIBLE,
				WS_OVERLAPPEDWINDOW,
			};
			DWORD _win32_wnd_style = NULL;
			for (size_t i = 0; i < style.size(); i++) if (style[i]) _win32_wnd_style |= style_map[i];
			return _win32_wnd_style;
		}

		HWND get_handle_window() {
			return **__init_wnd_prop.out_pp_hwnd;
		}
	}
}