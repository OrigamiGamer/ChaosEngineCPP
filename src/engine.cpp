#pragma once

#include "Engine.h"

namespace ChaosEngine {
	Engine::Engine() {
		running = false;
	}
	inline bool Engine::Initialize(INITIAL_ENGINE_PROPERTY& initial_property) {
		properties = initial_property;
		if (!graphic.initialize_graphic(properties.window->GetHandle())) return false;
		Engine::running = true;
		return true;
	}
	// Start a Game Loop
	bool Engine::Run() {
		if (!running) return false;
		// Game Loop
		while (running) {
			properties.window->Update();
			properties.on_update();
			graphic.begin_draw();
			properties.on_render();
			graphic.end_draw();
		}
		return true;
	}
	bool Engine::Shutdown() {
		running = false;
		if (!graphic.release_graphic()) return false;
		return true;
	}
}