#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace CompList {

		// Default unit of most varaibles about time: (ms)
		class Timer : public Model::CompModel {
		private:
			ULONGLONG t = 0;
			ULONGLONG last_t = 0;
			ULONGLONG delta_t = 0;
			ULONGLONG cached_t = 0;
			ULONGLONG last_event_t = 0;
			BOOL state_update = FALSE;

		public:
			ULONGLONG CountEventTotal = 0;
			ULONGLONG CountEventTodo = 0;
			ULONGLONG CycleTime = 0;


			void Init() {

			};
			//void Update() {

			//};
			//void Render() {

			//};
			void Release() {

			};


			// By default, the timer will not be working.
			void Create(OPTIONAL IN ULONGLONG newCycleTime = 1000) {
				this->CycleTime = newCycleTime;
				this->Clear();
			};

			void Clear(OPTIONAL IN ULONGLONG TargetEventCount = 0) {
				this->CountEventTodo = TargetEventCount;
				this->CountEventTotal = TargetEventCount;
				this->cached_t = 0;
			};

			void Begin() {
				state_update = TRUE;
			};

			void Pause() {
				state_update = FALSE;
			};

			// Stop the timer and clear the count of events total and todo.
			void Stop() {
				state_update = FALSE;
				Clear();
			};

			// TRUE returned means user can execute the codeblock as an event in "if";
			// FALSE returned means ignore the current tick.
			BOOL Todo(OPTIONAL OUT ULONGLONG* pTimeUsed = NULL) {
				t = GetTickCount64();
				
				// For the first run
				if (last_t == 0) {
					last_t = t;
					last_event_t = t;
				}

				if (t != last_t && state_update) {
					delta_t = t - last_t;	// get time used each cycle
					cached_t += delta_t;	// update the cached time

					// Create an event
					if (cached_t >= CycleTime) {
						this->CountEventTodo += 1;	// update count of events todo
						cached_t -= CycleTime;	// update the cached time

						// To do an event
						if (this->CountEventTodo > 0) {
							this->CountEventTodo -= 1;	// finish an event todo
							this->CountEventTotal += 1;	// log this event

							if (pTimeUsed != NULL) *pTimeUsed = t - last_event_t;
							last_event_t = t;

							return TRUE;
						}
					}
					
					last_t = t;	// update the last time
				}

				return FALSE;
			};

		};
	
	}

}
