#pragma once

#include "basic_wic.h"

namespace basic_chaos_engine {
	namespace DirectX {
		namespace WIC {
			IWICImagingFactory* wic_factory = nullptr;

			bool initialize_wic() {
				CoInitialize(nullptr);
				HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wic_factory));
				if (FAILED(hr)) return false;
				return true;
			}
			bool release_wic() {
				if (wic_factory != nullptr) wic_factory->Release();
				return true;
			}
		}
	}
}