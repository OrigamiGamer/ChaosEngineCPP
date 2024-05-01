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
		// ����һ�� the source which was created by buffer Ӧ��Ӧ���ӵ����棬�������� Play...
	}
	
	namespace _Test_ {

		void test_main() {
			OpenAL::Types::BufferID new_sound = OpenAL::LoadSoundFile("test.wav");


		}
	}

}
