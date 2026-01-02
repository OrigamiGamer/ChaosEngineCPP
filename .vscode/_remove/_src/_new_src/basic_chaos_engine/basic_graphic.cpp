#pragma once

#include "basic_Graphics.h"

namespace basic_chaos_engine {
	namespace basic_Graphics {
#ifdef _WIN32
#ifdef _D2D
		ID2D1Factory* d2d_factory = nullptr;
		ID2D1HwndRenderTarget* d2d_target = nullptr;
		ID2D1SolidColorBrush* brush = nullptr;

		bool initialize_Graphics(basic_window::HANDLE_WINDOW hwnd) {
			// initialize d2d
			if (!basic_Graphics_d2d::initialize_d2d(hwnd)) return false;
			d2d_factory = basic_Graphics_d2d::d2d_factory;
			d2d_target = basic_Graphics_d2d::d2d_target;
			// initialize brush
			HRESULT hr = d2d_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 1), &brush);
			if (FAILED(hr)) return false;
			return true;
		}
		bool release_Graphics() {
			if (!basic_Graphics_d2d::release_d2d()) return false;
			return true;
		}
		void set_brush_color(basic_Graphics::COLOR color) {
			brush->SetColor(color);
		}
		void begin_draw() { 
			d2d_target->BeginDraw();
		}
		void end_draw() {
			d2d_target->EndDraw();
		}

		void draw_point(basic_type::vec2<float> pos) {
			d2d_target->DrawLine({ pos.x,pos.y }, { pos.x,pos.y }, brush);
		}
		void draw_line(basic_type::vec2<float> pos1, basic_type::vec2<float> pos2) {
			d2d_target->DrawLine({ pos1.x,pos1.y }, { pos2.x,pos2.y }, brush);
		}
#endif
#endif
	}
}