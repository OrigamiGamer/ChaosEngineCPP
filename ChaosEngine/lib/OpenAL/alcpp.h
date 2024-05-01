#pragma once
#include "OpenAL.h"

namespace OpenAL {
	
	ALCdevice* _p_device = nullptr;
	ALCcontext* _p_context = nullptr;

	bool Initialize() {
		_p_device = alcOpenDevice(NULL);
		if (!_p_device) return false;

		_p_context = alcCreateContext(_p_device, NULL);
		if (!_p_context) { 
			alcCloseDevice(_p_device);
			return false;
		}

		alcMakeContextCurrent(_p_context);
		return true;
	}

	void Release() {
		alcDestroyContext(_p_context);
		alcCloseDevice(_p_device);
	}



	void Play() {
		// 考虑一下 the source which was created by buffer 应不应该扔到外面，或者留在 Play...
	}
	
	namespace _Test_ {

		void test_main() {
			OpenAL::Types::BufferID new_sound = OpenAL::LoadSoundFile("test.wav");


		}
	}

}
