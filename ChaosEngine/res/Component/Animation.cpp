#pragma once
#include "_list.cpp"

namespace ChaosEngine {

	namespace CompList {

		template <typename T_FLOAT>
		Animation<T_FLOAT>::Animation() {}

		template <typename T_FLOAT>
		void Animation<T_FLOAT>::Init() {}

		template <typename T_FLOAT>
		void Animation<T_FLOAT>::Update() {}

		template <typename T_FLOAT>
		void Animation<T_FLOAT>::Release() {}

		template <typename T_FLOAT>
		void Animation<T_FLOAT>::CreateEaseFunction(
			T_FLOAT& new_variable, EaseFunc<long double> new_ease_func,
			long double new_start_time
		) {
			//new_start_time
			vec_EaseFunc.push_back(new_ease_func);
			vec_pVariable.push_back(&new_variable);
		};

	}

}
