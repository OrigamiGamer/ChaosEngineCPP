#pragma once

#include "basic_graphic.h"

namespace basic_core {
	namespace basic_graphic {
#ifdef _WIN32
#ifdef _D2D
		ID2D1Factory* d2d_factory = nullptr;
		ID2D1HwndRenderTarget* d2d_target = nullptr;
		ID2D1SolidColorBrush* brush = nullptr;

		bool initialize_graphic(basic_window::HANDLE_WINDOW hwnd) {
			if (!basic_graphic_d2d::initialize_d2d(hwnd)) return false;
			d2d_factory = basic_graphic_d2d::d2d_factory;
			d2d_target = basic_graphic_d2d::d2d_target;
			return true;
		}
		bool release_graphic() {
			if (!basic_graphic_d2d::release_d2d()) return false;
			return true;
		}
		void set_brush_color() {
			//brush->SetColor();
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
		void draw_line() {

		}
#endif
#endif
	}
}