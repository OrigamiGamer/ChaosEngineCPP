#pragma once
#include "CompList.h"

namespace ChaosEngine {

	namespace CompList {

		class PhysicXEngine : public Model::CompModel {
		private:
			std::vector<Model::ObjectModel*> vec_lpObject;
				
		public:
			void Init() {};
			void Update() {
				for (UINT i = 0; i < vec_lpObject.size(); i++) {
					if (vec_lpObject[i]->use_physics) {
						DOUBLE a = vec_lpObject[i]->acceleration;
						
					};
				};
			};
			void Render() {};
			void Release() {};


			void Create() {};
			void RegObject(Model::ObjectModel* new_lpObject) {
				if (new_lpObject) vec_lpObject.push_back(new_lpObject);

			};

			// Exert a force on an Object.
			void Force(Model::ObjectModel& target_lpObject, DOUBLE F, DOUBLE Direction) {
				target_lpObject.acceleration = F / target_lpObject.mass;	// it needs addition to the force with direction,
				target_lpObject.direction;	// instead of resetting directly!
			};

		};

	}

}
