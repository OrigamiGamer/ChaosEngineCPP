#pragma once

#include <Windows.h>
#include <string>

namespace basic_window {
	HWND create_window(std::wstring title, int x, int y, int width, int height, HWND hwnd_parent = NULL,HINSTANCE hInstance) {
		LPWSTR cls_name = L"chaos_engine_window";
		WNDCLASSEXA* wndcls{};
		HWND hwnd = NULL;
		wndcls->cbSize = sizeof(*wndcls);
		wndcls->lpfnWndProc = nullptr;
		wndcls->lpszClassName = cls_name;
		wndcls->hInstance = NULL;
		wndcls->style = ;
		RegisterClassExW(&wndcls);

		hwnd = CreateWindowExW(
			NULL,
			cls_name,
			title.c_str(),
			NULL,
			x, y, width, height,
			hwnd_parent,
			NULL,
			NULL,
			NULL
		);

		WNDCLASS wc = {};
		wc.lpfnWndProc = s_DropDownWndProc;
		wc.cbWndExtra = sizeof(CTipACDialog*);
		wc.hInstance = g_hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.style = CS_SAVEBITS | CS_DROPSHADOW;
		wc.lpszClassName = s_wzClassName;
		RegisterClass(&wc);

		return hwnd;
	}
}