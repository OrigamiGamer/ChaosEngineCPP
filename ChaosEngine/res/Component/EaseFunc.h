#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace CompList {

		template <typename T_FLOAT>
		class EaseFunc : public Model::CompModel {
		private:
			bool state = false;
			long double max_progress = 1;	// (s)
			long double progress = 0;		// (s)

			T_FLOAT* p_variable = nullptr;
			T_FLOAT initial_value = 0;
			T_FLOAT target_value = 0;

		public:
			long double index = 1;

		public:
			EaseFunc();

			void Init();
			void Update();
			void Release();

			void Create(long double new_index, long double new_max_progress);
			void SetVariable(T_FLOAT& new_varaible);
			void Begin(T_FLOAT new_target_value);
			void Pause();	// TODO
			T_FLOAT GetResult();

		};

	}

}
