#pragma once

#include <Windows.h>
#include <wincodec.h>
#include <wincodecsdk.h>

namespace basic_chaos_engine {
	namespace DirectX {
		namespace WIC {
			extern IWICImagingFactory* wic_factory;

			bool initialize_wic();
			bool release_wic();
		}
	}
}