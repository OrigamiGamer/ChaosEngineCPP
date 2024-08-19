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
	bool Engine::Run() {
		if (!running) return false;
		// start two threads for update and render
		std::thread thread_update{ &Engine::EngineUpdate, this };
		std::thread thread_render{ &Engine::EngineRender, this };
		thread_update.detach();
		thread_render.detach();
		// start a loop for window update
		while (running) {
			last_time_window = get_system_time() / 1000ULL;
			// Window Update
			properties.window->Update();
			std::this_thread::sleep_for(properties.interval_window_update);
			// calculate time used
			delta_time_window = get_system_time() / 1000ULL - last_time_window;
		}
		return true;
	}
	bool Engine::Shutdown() {
		running = false;
		if (!graphic.release_graphic()) return false;
		return true;
	}
	void Engine::EngineUpdate() {
		long long _t = 0;
		while (running) {
			last_time_update = get_system_time() / 1000ULL;
			// Game Update
			properties.on_update();
			if (_t - last_time_update > properties.interval_game_update.count()) {
				_t = last_time_update;
				std::this_thread::sleep_for(properties.interval_game_update);
			}
			// calculate time used
			delta_time_update = get_system_time() / 1000ULL - last_time_update;
		}
	}
	void Engine::EngineRender() {
		while (running) {
			last_time_render = get_system_time() / 1000ULL;
			// Game Render
			graphic.begin_draw();
			properties.on_render();
			graphic.end_draw();
			std::this_thread::sleep_for(properties.interval_game_render);
			// calculate time used
			delta_time_render = get_system_time() / 1000ULL - last_time_render;
		}
	}
}