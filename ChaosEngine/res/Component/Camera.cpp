#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace CompList {

		Camera::Camera() {
			this->viewPos = {};
			this->viewSize = {};
			this->viewScale = {};
		}

		void Camera::Init() {}
		void Camera::Update() {}
		void Camera::Release() {}

		void Camera::Create() {}
	}

}
