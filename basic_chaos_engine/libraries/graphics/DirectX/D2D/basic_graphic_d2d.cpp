#pragma once

#include "basic_graphic_d2d.h"

namespace basic_chaos_engine {
	basic_graphic_d2d::basic_graphic_d2d() {
		ID2D1Factory* d2d_factory = nullptr;
		ID2D1HwndRenderTarget* d2d_target = nullptr;
	}

	bool basic_graphic_d2d::initialize_d2d(HWND hwnd) {
		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &d2d_factory);
		if (FAILED(hr)) return false;

		D2D1_RENDER_TARGET_PROPERTIES target_prop{};
		float dpi = (float)GetDpiForWindow(hwnd);
		target_prop.dpiX = dpi;
		target_prop.dpiY = dpi;
		target_prop.type = D2D1_RENDER_TARGET_TYPE_HARDWARE;
		target_prop.usage = D2D1_RENDER_TARGET_USAGE_NONE;
		target_prop.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
		target_prop.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
		target_prop.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;

		D2D1_HWND_RENDER_TARGET_PROPERTIES hwnd_target_prop{};
		hwnd_target_prop.hwnd = hwnd;
		RECT rc; GetWindowRect(hwnd, &rc);
		hwnd_target_prop.pixelSize = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
		hwnd_target_prop.presentOptions = D2D1_PRESENT_OPTIONS_IMMEDIATELY;

		hr = d2d_factory->CreateHwndRenderTarget(target_prop, hwnd_target_prop, &d2d_target);
		if (FAILED(hr)) return false;
		return true;
	}
	bool basic_graphic_d2d::release_d2d() {
		if (d2d_factory != nullptr) d2d_factory->Release();
		return true;
	}
}