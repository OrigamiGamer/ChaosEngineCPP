#pragma once

#include <string>

namespace ChaosEngine {
	struct WINDOW_PROPERTY {
		unsigned int width, height;
		int pos;
		std::wstring title = L"New Window";
	};

	class Window;
	class Window {
		bool initialize(WINDOW_PROPERTY win_prop);
	};
}
