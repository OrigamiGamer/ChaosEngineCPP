#pragma once

#ifdef _DEBUG
// Debugging Definitions
#define UNICODE
#define _D2D
#define _OPENAL
#endif

// CPP_STL
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <array>
#include <bitset>
#include <map>
#include <unordered_map>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>

#include "basic_type.h"

// multi-platform
#ifdef _WIN32
#include <Windows.h>
#ifdef _D2D
#include <wincodec.h>
#include <d2d1.h>
#endif
#endif

namespace program {
	// Get the current directory.
	inline std::wstring get_root_directory();
	// Tramsform a relative path to an absolute path.
	inline std::wstring locate(const std::wstring& filename);
}

namespace basic_chaos_engine {
	struct Const {
		static constexpr int DEFAULT = INT_MAX;
		static UINT WM_GAME_INIT;
		struct WindowStyle {
			static constexpr int VISIBLE = 1;
			static constexpr int DEFAULT = 1 << 1;
		};
	};
#ifdef UNICODE
	UINT Const::WM_GAME_INIT = RegisterWindowMessageW(L"WM_GAME_INIT");
#else
	UINT Const::WM_GAME_INIT = RegisterWindowMessageA("WM_GAME_INIT");
#endif

	namespace type {
		// basic_window
#ifdef _WIN32
		typedef HWND HANDLE_WINDOW;
#elif __linux__
		typedef void* HANDLE_WINDOW;	// ?
#endif
		typedef bool (*ON_INIT)();
		typedef bool (*ON_EXIT)();

		struct INITIAL_WINDOW_PROPERTY;
		class basic_window;
	}
}

#include "graphics/basic_common_graphic.h"

#include "audio/basic_common_audio.h"