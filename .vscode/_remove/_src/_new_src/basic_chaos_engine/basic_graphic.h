#pragma once

#include "basic_common.h"
#include "library/DirectX/D2D/basic_Graphics_d2d.h"

namespace basic_chaos_engine {
	namespace basic_Graphics {
#ifdef _D2D
		extern ID2D1Factory* d2d_factory;
		extern ID2D1HwndRenderTarget* d2d_target;
		extern ID2D1SolidColorBrush* brush;
#endif
		bool initialize_Graphics(basic_window::HANDLE_WINDOW hwnd);
		bool release_Graphics();

		// watch out how to process the two conditions of common Graphicsal interfaces between 2D and 3D
		void set_brush_color(basic_Graphics::COLOR color);
		void begin_draw();
		void end_draw();
#ifdef _D2D
		void draw_point(basic_type::vec2<float> pos);
		void draw_line();
#endif
	}
}