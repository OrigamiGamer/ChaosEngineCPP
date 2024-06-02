#pragma once
#include "ResList.h"

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
			VirtKeyStateBuffer();
			void Init();
			void Release();

		private:
			inline BOOL IsValid(int new_nVirtKey);

		public:
			BOOL GetState(int new_nVirtKey);
			BOOL OnKeyDown(int new_nVirtKey);
			BOOL OnKeyUp(int new_nVirtKey);

		};

	}

}
