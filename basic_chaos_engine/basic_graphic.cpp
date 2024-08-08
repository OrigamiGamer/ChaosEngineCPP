#pragma once

#include "basic_graphic.h"

namespace basic_chaos_engine {
#ifdef _WIN32
#ifdef _D2D
	basic_graphic::basic_graphic() {
		stroke_width = 1.0f;
		d2d_factory = nullptr;
		d2d_target = nullptr;
		brush = nullptr;
	}
	// basic interfaces
	bool basic_graphic::initialize_graphic(HANDLE_WINDOW hwnd) {
		// initialize d2d
		if (!basic_graphic_d2d::initialize_d2d(hwnd)) return false;
		d2d_factory = basic_graphic_d2d::d2d_factory;
		d2d_target = basic_graphic_d2d::d2d_target;
		// initialize brush
		HRESULT hr = d2d_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 1), &brush);
		if (FAILED(hr)) return false;
		return true;
	}
	bool basic_graphic::release_graphic() {
		if (!basic_graphic_d2d::release_d2d()) return false;
		return true;
	}
	inline void basic_graphic::set_stroke_width(float width) {
		stroke_width = width > 0.0f ? width : 0.0f;
	}
	inline void basic_graphic::set_brush_color(COLOR color) {
		brush->SetColor(color);
	}
	inline void basic_graphic::begin_draw() {
		d2d_target->BeginDraw();
		d2d_target->Clear(D2D1::ColorF(D2D1::ColorF::Black, 1));
	}
	inline void basic_graphic::end_draw() {
		d2d_target->EndDraw();
	}
	// drawing interfaces
	void basic_graphic::draw_circle(basic_type::vec2<float> center_pos, basic_type::vec2<float> radius) {
		D2D1_ELLIPSE ellipse{};
		ellipse.point = D2D1::Point2F(center_pos.x, center_pos.y);
		ellipse.radiusX = radius.x;
		ellipse.radiusY = radius.y;
		d2d_target->DrawEllipse(ellipse, brush, stroke_width);
	}
	void basic_graphic::draw_line(basic_type::vec2<float> pos1, basic_type::vec2<float> pos2) {
		d2d_target->DrawLine({ pos1.x,pos1.y }, { pos2.x,pos2.y }, brush, stroke_width);
	}
#endif
#endif
}