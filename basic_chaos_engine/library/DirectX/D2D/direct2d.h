#pragma once

#include <Windows.h>
#include <wincodec.h>
#include <dxgi.h>
#include <d2d1.h>
#include <dwrite.h>

namespace basic_chaos_engine {
	namespace D2D {
		extern ID2D1Factory* d2d_factory;
		extern ID2D1HwndRenderTarget* d2d_hwndRenderTarget;

		bool initialize_d2d(D2D1_SIZE_U wnd_size, HWND hwnd);
	}
}


namespace basic_window {

}