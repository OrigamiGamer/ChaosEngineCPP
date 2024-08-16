#pragma once

#pragma comment(lib,"d2d1.lib")

#include <Windows.h>
#include <wincodec.h>
#include <dxgi.h>
#include <d2d1.h>
#include <dwrite.h>

namespace basic_chaos_engine {
	class basic_graphic_d2d {
	public:
		ID2D1Factory* d2d_factory;
		ID2D1HwndRenderTarget* d2d_target; // d2d_hwnd_render_target

		basic_graphic_d2d();
		bool initialize_d2d(HWND hwnd);
		bool release_d2d();
	};
}