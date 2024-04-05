#pragma once
#include "_list.cpp"

namespace ChaosEngine {

	namespace Type {

		VirtKeyStateBuffer::VirtKeyStateBuffer() {
			vec_buffer;
			vec_buffer.resize(254);
		}

		void VirtKeyStateBuffer::Init() {}
		void VirtKeyStateBuffer::Release() {}
	
		// If the return value is -1, the parameter is invalid.
		BOOL VirtKeyStateBuffer::GetState(int new_nVirtKey) {
			BOOL vk_state = -1;
			if (-1 < new_nVirtKey && new_nVirtKey < vec_buffer.size()) {
				vk_state = GetKeyState(new_nVirtKey);
				vec_buffer[new_nVirtKey].current = vk_state;
				return vk_state < 0;
			}
			return FALSE;
		}

		BOOL VirtKeyStateBuffer::OnKeyDown(int new_nVirtKey){
			BOOL vk_state = GetState(new_nVirtKey);
			if (vk_state != -1) {
				if (vec_buffer[new_nVirtKey].last != vec_buffer[new_nVirtKey].current) {
					vec_buffer[new_nVirtKey].last = vec_buffer[new_nVirtKey].current;
					return vk_state < 0;
				}
			}
			return FALSE;
		}

		BOOL VirtKeyStateBuffer::OnKeyUp(int new_nVirtKey) {
			BOOL vk_state = GetState(new_nVirtKey);
			if (vk_state != -1) {
				if (vec_buffer[new_nVirtKey].last != vec_buffer[new_nVirtKey].current) {
					vec_buffer[new_nVirtKey].last = vec_buffer[new_nVirtKey].current;
					return vk_state == 0;
				}
			}
			return FALSE;
		}

	}

}
