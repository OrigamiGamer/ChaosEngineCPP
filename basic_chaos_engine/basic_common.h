#pragma once

// DEBUG definitions
#define UNICODE
#define _D2D
// DEBUG

#include <stdexcept>
#include <vector>
#include <bitset>
#include <map>
#include <unordered_map>
#include <string>
#include <array>
#include <thread>

#include "basic_type.h"

// multi-platform
#ifdef _WIN32
#include <Windows.h>
#ifdef _D2D
#include <wincodec.h>
#include <d2d1.h>
#endif
#endif

namespace basic_chaos_engine {
#ifdef _WIN32

#ifdef UNICODE
	const UINT WM_GAME_INIT = RegisterWindowMessageW(L"WM_GAME_INIT");
#else
	const UINT WM_GAME_INIT = RegisterWindowMessageA("WM_GAME_INIT");
#endif

	typedef HWND HANDLE_WINDOW;
#elif __linux
#endif

	struct Const {
		static constexpr int DEFAULT = INT_MAX;
	};
	struct WindowStyle {
		static constexpr int VISIBLE = 1;
		static constexpr int DEFAULT = 1 << 1;
	};
	typedef bool (*ON_INIT)();
	typedef bool (*ON_EXIT)();

	struct INITIAL_WINDOW_PROPERTY;

#ifdef _D2D
	typedef D2D1_COLOR_F COLOR;
#endif
}