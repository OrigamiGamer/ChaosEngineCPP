#pragma once

#include <stdexcept>
#include <vector>
#include <bitset>
#include <string>
#include <array>
#include <thread>

#include "basic_type.h"

namespace basic_core {
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
		struct INITIAL_WINDOW_PROPERTY;
	}
}