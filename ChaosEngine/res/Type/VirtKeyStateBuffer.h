#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace Type {

		struct VirtKeyState {
			BOOL current = FALSE;
			BOOL last = FALSE;
		};

		class VirtKeyStateBuffer : public Model::PropertyModel {
		private:
			std::vector<VirtKeyState> vec_buffer;

		public:

		public:
			VirtKeyStateBuffer();
			void Init();
			void Release();

			BOOL GetState(int new_nVirtKey);
			BOOL OnKeyDown(int new_nVirtKey);
			BOOL OnKeyUp(int new_nVirtKey);

		};

	}

}
