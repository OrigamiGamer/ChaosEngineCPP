#pragma once

#include "VirtKeyStateBuffer.h"

namespace basic_type {
	VirtKeyStateBuffer::VirtKeyStateBuffer() {
		vec_buffer.resize(254);
		vec_down_buffer.resize(254);
		vec_up_buffer.resize(254);
	}

	inline BOOL VirtKeyStateBuffer::IsValid(int new_nVirtKey) {
		if (-1 < new_nVirtKey && new_nVirtKey < vec_buffer.size()) return TRUE;
		return FALSE;
	}

	BOOL VirtKeyStateBuffer::GetState(int new_nVirtKey) {
		if (IsValid(new_nVirtKey)) {
			BOOL vk_state = GetKeyState(new_nVirtKey);
			vec_buffer[new_nVirtKey].current = vk_state;
			return vk_state & 0x8000;
		}
		return FALSE;
	}

	BOOL VirtKeyStateBuffer::OnKeyDown(int new_nVirtKey) {
		if (IsValid(new_nVirtKey)) {
			BOOL vk_state = GetKeyState(new_nVirtKey);
			vec_down_buffer[new_nVirtKey].current = vk_state;
			if (vec_down_buffer[new_nVirtKey].last != vec_down_buffer[new_nVirtKey].current) {
				vec_down_buffer[new_nVirtKey].last = vec_down_buffer[new_nVirtKey].current;
				return vk_state & 0x8000;
			}
		}
		return FALSE;
	}

	BOOL VirtKeyStateBuffer::OnKeyUp(int new_nVirtKey) {
		if (IsValid(new_nVirtKey)) {
			BOOL vk_state = GetKeyState(new_nVirtKey);
			vec_up_buffer[new_nVirtKey].current = vk_state;
			if (vec_up_buffer[new_nVirtKey].last != vec_up_buffer[new_nVirtKey].current) {
				vec_up_buffer[new_nVirtKey].last = vec_up_buffer[new_nVirtKey].current;
				return !(vk_state & 0x8000);
			}
		}
		return FALSE;
	}
}