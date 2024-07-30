#pragma once

#include "direct2d.h"

namespace basic_chaos_engine {
	namespace D2D {
		ID2D1Factory* d2d_factory = nullptr;
		ID2D1HwndRenderTarget* d2d_hwnd_render_target = nullptr;

		bool initialize_d2d(D2D1_SIZE_U wnd_size, HWND hwnd) {
			HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory);
			if (FAILED(hr)) return false;

			D2D1_RENDER_TARGET_PROPERTIES target_prop{};
			target_prop.dpiX;
			target_prop.dpiY;
			target_prop.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
			target_prop.usage = D2D1_RENDER_TARGET_USAGE_NONE;
			target_prop.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
			target_prop.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
			target_prop.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;

			D2D1_HWND_RENDER_TARGET_PROPERTIES hwnd_target_prop{};
			hwnd_target_prop.hwnd = hwnd;
			hwnd_target_prop.pixelSize = wnd_size;
			hwnd_target_prop.presentOptions = D2D1_PRESENT_OPTIONS_NONE;

			hr = d2d_factory->CreateHwndRenderTarget(target_prop, hwnd_target_prop, &d2d_hwnd_render_target);
			if (FAILED(hr)) return false;

			return true;
		}
	}
}