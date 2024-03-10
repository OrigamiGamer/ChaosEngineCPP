#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace Type {

		class Camera : public Model::PropertyModel {
		private:

		public:
			Type::POS viewPos{};
			Type::SIZE viewSize{};
			Type::SCALE viewScale{ 1, 1, 1 };
			Type::POS mouseOffsetPos;

			Model::ObjectModel* pTrackingObject = nullptr;	// track the object  ???? �ӽǰ󶨵�ָ������

			Camera();
			void Init();
			void Update();
			void Release();

			void Create();

		};

	}

}
