#pragma once

#include <stdexcept>
#include <vector>
#include <bitset>
#include <string>
#include <array>

namespace basic_chaos_engine {
	namespace basic_window {
		enum WINDOW_STYLE {
			VISIBLE = 1,
			DEFAULT = 1 << 1,
		};
		typedef bool (*ON_INIT)();
		typedef bool (*ON_EXIT)();
	}
}