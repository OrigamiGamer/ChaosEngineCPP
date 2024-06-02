#pragma once
#include "ResList.h"

namespace ChaosEngine {

	namespace Type {

		template <typename T_FLOAT>
		struct STD_ANIMATION_PROPERTY_LIST {
			CompList::EaseFunc<long double> ease_func;
			T_FLOAT* p_variable = nullptr;			// !! dangerous, but notice how to process nullptr !!
			long double start_time;
		};

	}

	namespace CompList {

		template <typename T_FLOAT>
		class Animation : public Model::CompModel {
		private:
			std::vector<Type::STD_ANIMATION_PROPERTY_LIST<T_FLOAT>> vec_ani;
			bool state = false;
			long double progress;		// playing progress
			long double max_progress;	// max playing progress

		public:
			std::wstring id_name;	// animation identity name
			bool is_loop_playback = false;

		public:
			Animation();

			void Init();
			void Update();
			void Release();
			
			inline void CreateEaseFunction(
				T_FLOAT& new_variable, EaseFunc<long double> new_ease_func,
				long double new_start_time
			);
			inline void ClearProgress();
			inline void Play();
			inline void Pause();
			inline void Continue();
			inline void Stop();

		};

	}

}
