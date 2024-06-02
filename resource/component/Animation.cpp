#pragma once
#include "ResList.cpp"

namespace ChaosEngine {

	namespace CompList {

		template <typename T_FLOAT>
		Animation<T_FLOAT>::Animation() {}

		template <typename T_FLOAT>
		void Animation<T_FLOAT>::Init() {}

		template <typename T_FLOAT>
		void Animation<T_FLOAT>::Update() {

			if (state) {
				if (progress < max_progress) progress += EngineX::deltaTime;

				for (Type::STD_ANIMATION_PROPERTY_LIST<T_FLOAT> ani : vec_ani) {
					// Start playing a ease-function.
					if (ani.start_time >= this->progress) {
						if (ani.ease_func.GetPlayingState() == false) ani.ease_func.Continue();
						ani.ease_func.Update();
						ani.p_variable = ani.ease_func.GetSingleResult();
						//ani.ease_func.SetNewValue(, );	// TODO: dynamicly update initial and target values
					}

				}
				
				if (progress >= max_progress) {
					progress = max_progress;

					if (is_loop_playback) {
						ClearProgress();
					}
					else {
						state = false;
					}
				}
			}

		}

		template <typename T_FLOAT>
		void Animation<T_FLOAT>::Release() {}

		template <typename T_FLOAT>
		inline void Animation<T_FLOAT>::CreateEaseFunction(
			T_FLOAT& new_variable, EaseFunc<long double> new_ease_func,
			long double new_start_time
		) {
			Type::STD_ANIMATION_PROPERTY_LIST<T_FLOAT> ani;
			ani.ease_func = new_ease_func;
			ani.p_variable = &new_variable;
			ani.start_time = new_start_time;
			vec_ani.push_back(ani);

			this.max_progress += ani.ease_func.GetTimeLength() + new_start_time - max_progress;	// compute max playing progress
		}

		template <typename T_FLOAT>
		inline void Animation<T_FLOAT>::ClearProgress() {
			progress = 0;
		}

		template <typename T_FLOAT>
		inline void Animation<T_FLOAT>::Play() {
			ClearProgress();
			state = true;
		}

		template <typename T_FLOAT>
		inline void Animation<T_FLOAT>::Pause() {
			state = false;
		}

		template <typename T_FLOAT>
		inline void Animation<T_FLOAT>::Continue() {
			state = true;
		}

		template <typename T_FLOAT>
		inline void Animation<T_FLOAT>::Stop() {
			ClearProgress();
			state = false;
		}

	}

}
