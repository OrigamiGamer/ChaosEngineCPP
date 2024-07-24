#pragma once

#include "basic_window_win.h"

namespace basic_chaos_engine {
	namespace basic_window_win {
		HWND create_window(INITIAL_WINDOW_PROPERTY init_wnd_prop) {
			LPWSTR cls_name = L"chaos_engine_window";
			WNDCLASSEXW wndcls{};
			HWND hwnd = NULL;
			wndcls.cbSize = sizeof(wndcls);
			wndcls.lpfnWndProc = &wnd_proc;
			wndcls.lpszClassName = cls_name;
			wndcls.hInstance = NULL;
			wndcls.style = CS_HREDRAW | CS_VREDRAW;
			//wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
			RegisterClassExW(&wndcls);

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
			);
			//ShowWindow(hwnd, SW_SHOW);
			UpdateWindow(hwnd);
			__init_wnd_prop = init_wnd_prop;

			MSG msg = {};
			while (GetMessage(&msg, NULL, 0, 0) > 0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return hwnd;
		}

		LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			switch (msg) {
			case WM_CREATE:
				if (__init_wnd_prop.on_init != nullptr)
					if (!__init_wnd_prop.on_init()) DestroyWindow(hwnd);
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
			if (__init_wnd_prop.wnd_proc != nullptr)
				return __init_wnd_prop.wnd_proc(hwnd, msg, wparam, lparam);
			return DefWindowProcW(hwnd, msg, wparam, lparam);
		}
		DWORD tranform_style(std::bitset<32> style) {
			// !! The order of this map is connected to the order of the basic_window::WINDOW_STYLE !!
			const std::array<DWORD, 32> style_map = {
				WS_VISIBLE,
				WS_OVERLAPPEDWINDOW,
			};
			DWORD _win32_wnd_style = NULL;
			for (size_t i = 0; i < style.size(); i++)
				if (style[i]) _win32_wnd_style |= style_map[i];
			return _win32_wnd_style;
		}
	}
}