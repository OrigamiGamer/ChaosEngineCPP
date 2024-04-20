#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace CompList {

		template <typename T_FLOAT>
		class Animation : public Model::CompModel {
		private:
			std::vector<EaseFunc<T_FLOAT>> vec_EaseFunc;
			std::vector<T_FLOAT*> vec_pVariable;			// !! dangerous !!

		public:
			std::wstring IdName;

		public:
			Animation();

			void Init();
			void Update();
			void Release();
			void Animation<T_FLOAT>::CreateEaseFunction(
				T_FLOAT& new_variable, EaseFunc<long double> new_ease_func,
				long double new_start_time
			);
			void Play();

		};

	}

}
