#pragma once

#include "Engine.h"

namespace ChaosEngine {
	Engine::Engine() {
		running = false;
		last_time_update = 0;
		last_time_render = 0;
		last_time_window = 0;
		delta_time_update = 0;
		delta_time_render = 0;
		delta_time_window = 0;
		fps = 0;
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
		unsigned long long _t = 0;
		unsigned long long frame_count = 0;
		unsigned long long last_time = 0;
		while (running) {
			last_time_update = get_system_time() / 1000ULL;
			// Game Update
			properties.on_update();
			// calculate time used
			delta_time_update = get_system_time() / 1000ULL - last_time_update;
			_t = ((unsigned long long)properties.interval_game_update.count() - delta_time_update);
			if (_t > 0) std::this_thread::sleep_for(std::chrono::milliseconds(_t));
			// calculate fps
			frame_count++;
			if (frame_count >= 100) {
				fps = 100.0f / (last_time_update - last_time);
				frame_count = 0;
				last_time = last_time_update;
			}
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