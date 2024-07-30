#pragma once

#include <vector>

// Windows
#include "Windows.h"

namespace type {
	struct VirtKeyState {
		BOOL current = FALSE;
		BOOL last = FALSE;
	};

	class VirtKeyStateBuffer {	// rename -> vk_state_stream
	private:
		std::vector<VirtKeyState> vec_buffer, vec_down_buffer, vec_up_buffer;
	public:
		VirtKeyStateBuffer();
	private:
		inline BOOL IsValid(int new_nVirtKey);
	public:
		BOOL GetState(int new_nVirtKey);
		BOOL OnKeyDown(int new_nVirtKey);
		BOOL OnKeyUp(int new_nVirtKey);
	};
}