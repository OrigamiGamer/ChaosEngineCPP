#pragma once
#include "_list.cpp"

namespace ChaosEngine {

	namespace CompList {

		template <typename T_FLOAT>
		EaseFunc<T_FLOAT>::EaseFunc() {
			state = false;
			max_progress = 0.4;	// (s)
			progress = 0;

			index = 1;		// linear
			p_variable = nullptr;
			initial_value = 0;
			target_value = 0;
		}

		template <typename T_FLOAT>
		void EaseFunc<T_FLOAT>::Init() {}

		template <typename T_FLOAT>
		void EaseFunc<T_FLOAT>::Update() {
			
		}

		template <typename T_FLOAT>
		void EaseFunc<T_FLOAT>::Release() {}

		template <typename T_FLOAT>
		void EaseFunc<T_FLOAT>::Create(long double new_index, long double new_max_progress) {
			index = new_index;
			max_progress = new_max_progress;
		}

		template <typename T_FLOAT>
		void EaseFunc<T_FLOAT>::SetVariable(T_FLOAT& new_varaible) {
			p_variable = &new_varaible;
		}

		template <typename T_FLOAT>
		void EaseFunc<T_FLOAT>::Begin(T_FLOAT new_target_value) {
			state = true;
			progress = 0;
			if (p_variable != nullptr) initial_value = *p_variable;
			target_value = new_target_value;

		}

		template <typename T_FLOAT>
		T_FLOAT EaseFunc<T_FLOAT>::GetResult() {
			T_FLOAT single_result = 0;
			if (state) {
				if (progress < max_progress) {
					progress += EngineX::deltaTime;
				}
				if (progress >= max_progress) {
					progress = EngineX::deltaTime;
					state = false;
				}
				long double percent = progress / max_progress;

				// index function
				single_result = initial_value + (target_value - initial_value) * (T_FLOAT)pow(percent, index);	// len += (d_len)*t^a

				/*if (p_varaible != nullptr) {
					*p_varaible = single_result;
				}*/
				return single_result;
			}
			return target_value;
		}

	}

}
