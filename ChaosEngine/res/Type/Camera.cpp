#pragma once
#include "_list.cpp"

namespace ChaosEngine {

	namespace Type {

		Camera::Camera() {
			this->viewPos = {};
			this->viewSize = {};
			this->viewScale = { 1, 1, 1 };
			this->mouseOffsetPos = {};
			
			this->pObjectPos = {};
		}

		void Camera::Init() {}
		void Camera::Update() {
			this->mouseOffsetPos = WindowX::Prop::MousePos + viewPos; // Update the mouse offset position.
		}
		void Camera::Release() {}

		void Camera::Create() {}

	}

}
