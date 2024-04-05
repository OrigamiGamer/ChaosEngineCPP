#pragma once
#include "_list.cpp"

namespace ChaosEngine {

	namespace Type {

		Camera::Camera() {
			this->viewPos = {};
			this->viewSize = {};
			this->viewScale = { 1, 1, 1 };
			this->mouseOffsetPos = {};
		}

		void Camera::Init() {}
		void Camera::Update() {
			this->mouseOffsetPos = WindowX::Prop::MousePos + viewPos; // Update the mouse offset position.
		}
		void Camera::Release() {}

		//// Track the center position of the object
		//void Camera::TrackObject(Model::ObjectModel& new_object) {
		//	this->pTrackingObject = &new_object;
		//}

	}

}
