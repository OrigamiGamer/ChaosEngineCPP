#pragma once

// DEBUG definitions
#define _D2D
// DEBUG

#include <stdexcept>
#include <vector>
#include <bitset>
#include <string>
#include <array>
#include <thread>

#include "basic_type.h"

#ifdef _WIN32
#include <Windows.h>
#ifdef _D2D
#include <wincodec.h>
#include <d2d1.h>
#endif
#endif

namespace basic_chaos_engine {
	namespace basic_window {
		struct Const {
			static constexpr int DEFAULT = INT_MAX;
		};
		struct WindowStyle {
			static constexpr int VISIBLE = 1;
			static constexpr int DEFAULT = 1 << 1;
		};
		typedef bool (*ON_INIT)();
		typedef bool (*ON_EXIT)();
#ifdef _WIN32
		typedef HWND HANDLE_WINDOW;
#endif
		struct INITIAL_WINDOW_PROPERTY;
	}

	namespace basic_Graphics {
#ifdef _D2D
		typedef D2D1_COLOR_F COLOR;
#endif
	}
}