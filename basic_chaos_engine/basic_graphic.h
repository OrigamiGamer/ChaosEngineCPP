#pragma once

#include "basic_common.h"
#include "library/graphic/DirectX/D2D/basic_graphic_d2d.h"

namespace basic_chaos_engine {
	class basic_graphic {
#ifdef _D2D
	private:
		basic_graphic_d2d _graphic;
		ID2D1Factory* d2d_factory;
		ID2D1HwndRenderTarget* d2d_target;
		ID2D1SolidColorBrush* brush;
#endif
	public:
		float stroke_width;

		basic_graphic();
		bool initialize_graphic(type::HANDLE_WINDOW hwnd);
		bool release_graphic();
		// watch out how to process the two conditions of common graphical interfaces between 2D and 3D
		inline void set_stroke_width(float width);
		inline void set_brush_color(type::COLOR color);
		inline void begin_draw();
		inline void end_draw();
#ifdef _D2D
		void draw_line(basic_type::vec2<float> pos1, basic_type::vec2<float> pos2);
		void draw_circle(basic_type::vec2<float> center_pos, basic_type::vec2<float> radius = { 1.0f,1.0f });
		inline void draw_circle(basic_type::vec2<float> center_pos, float radius);
#endif
	};
}