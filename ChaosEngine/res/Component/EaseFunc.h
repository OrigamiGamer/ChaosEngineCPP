#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace Type {
		enum EASE_FUNC {
			EASE_FUNC_INDEX_IN = 0,
			EASE_FUNC_INDEX_OUT = 1,
			EASE_FUNC_INDEX_INOUT = 2
		};
	}

	namespace CompList {

		template <typename T_FLOAT>
		class EaseFunc : public Model::CompModel {
		private:

		public:
			bool state = false;			// updating state
			long double g = 0;			// progress, unit: second
			long double g_max = 1.0;	// max progress
			long double t = 0;			// process
			long double a = 1;			// index of the index-function
			long double p = 0;			// percent
			unsigned int n;				// ease function type
			long double x = 0;			// initial value
			long double x_t = 0;		// target value
			long double dx = 0;			// delta value

		public:
			EaseFunc();

			void Init();
			void Init(
				T_FLOAT new_initial_x, T_FLOAT new_target_x,
				unsigned int new_function_type, long double new_index, long double new_time_length
			);

			void Update();
			void Release();

			T_FLOAT GetSingleResult();
			void SetNewValue(T_FLOAT new_initial_value, T_FLOAT new_target_value);
			void ClearProgress();
			void Begin();
			void Pause();
			void Stop();

		};

	}

}
