#pragma once
#include "_list.cpp"

namespace ChaosEngine {

	namespace CompList {

		template <typename T_FLOAT>
		EaseFunc<T_FLOAT>::EaseFunc() { }

		// Initialize by default properties. It will stop updating and clear progress.
		template <typename T_FLOAT>
		void EaseFunc<T_FLOAT>::Init() {
			state = false;
			n = Type::EASE_FUNC_INDEX_OUT;
			a = 2;
			g = 0.0;
			g_max = 1.0;

			SetNewValue(0, 0);
		}

		// Initialize by user properties. It will stop updating and clear progress.
		template <typename T_FLOAT>
		void EaseFunc<T_FLOAT>::Init(
			T_FLOAT new_initial_x, T_FLOAT new_target_x,
			unsigned int new_function_type, long double new_index, long double new_time_length
		) {
			state = false;
			n = new_function_type;
			a = new_index;
			g = 0.0;
			g_max = new_time_length;

			SetNewValue(new_initial_x, new_target_x);
		}

		template <typename T_FLOAT>
		void EaseFunc<T_FLOAT>::Update() {
			if (state == true) {

				if (g < g_max) {
					g += EngineX::deltaTime;
				}
				else {
					g = g_max;
					state = false;
				}

				t = g / g_max;

				switch (n) {
				case Type::EASE_FUNC_INDEX_IN:
					p = pow(t, a);

					break;
				case Type::EASE_FUNC_INDEX_OUT:
					p = -pow(abs(t - 1), a) + 1;

					break;
				case Type::EASE_FUNC_INDEX_INOUT:
					if (t <= 0.5) {
						p = pow(2, a - 1) * pow(t, a);
					}
					else if (t > 0.5) {
						p = -pow(2, a - 1) * pow(abs(t - 1), a) + 1;
					}

					break;
				}

				result = x + dx * p;
			}
		}

		template <typename T_FLOAT>
		void EaseFunc<T_FLOAT>::Release() {}

		template <typename T_FLOAT>
		inline T_FLOAT EaseFunc<T_FLOAT>::GetSingleResult() {
			return static_cast<T_FLOAT>(result);
		}

		template <typename T_FLOAT>
		inline void EaseFunc<T_FLOAT>::SetNewValue(T_FLOAT new_initial_x, T_FLOAT new_target_x) {
			x = static_cast<long double>(new_initial_x);
			x_t = static_cast<long double>(new_target_x);
			dx = x_t - x;
			result = x;
		}

		template <typename T_FLOAT>
		inline void EaseFunc<T_FLOAT>::ClearProgress() {
			g = 0.0;
			t = 0.0;
			p = 0.0;
		}

		template <typename T_FLOAT>
		inline void EaseFunc<T_FLOAT>::Begin() {
			ClearProgress();
			state = true;
		}

		template <typename T_FLOAT>
		inline void EaseFunc<T_FLOAT>::Pause() {
			state = false;
		}

		template <typename T_FLOAT>
		inline void EaseFunc<T_FLOAT>::Continue() {
			state = true;
		}

		template <typename T_FLOAT>
		inline void EaseFunc<T_FLOAT>::Stop() {
			state = false;
			ClearProgress();
		}

		template <typename T_FLOAT>
		inline bool EaseFunc<T_FLOAT>::GetPlayingState() {
			return state;
		};

		template <typename T_FLOAT>
		inline long double EaseFunc<T_FLOAT>::GetTimeLength() {
			return g_max;
		};

		template <typename T_FLOAT>
		inline T_FLOAT EaseFunc<T_FLOAT>::GetInitialValue() {
			return x;
		};

		template <typename T_FLOAT>
		inline T_FLOAT EaseFunc<T_FLOAT>::GetTargetValue() {
			return x_t;
		};

	}

}
