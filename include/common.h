#pragma once

#include "basic_type.h"

namespace ChaosEngine {
	class Window;

	typedef void (*ON_UPDATE)();
	typedef void (*ON_RENDER)();

	struct INITIAL_ENGINE_PROPERTY {
		Window* window = nullptr;
		ON_UPDATE on_update = nullptr;
		ON_RENDER on_render = nullptr;
	};
	class Engine;
}