#pragma once
#include "al.h"
#include "alc.h"
#include <vector>
#include <fstream>

namespace OpenAL {

	namespace Types {

#pragma pack(push,1)
		struct WavHeaderInfo {
			uint32_t chunkID;
			uint32_t chunkSize;
			uint32_t format;
			uint32_t subchunk1ID;
			uint32_t subchunk1Size;
			uint16_t audioFormat;
			uint16_t numChannels;
			uint32_t sampleRate;
			uint32_t byteRate;
			uint16_t blockAlign;
			uint16_t bitsPerSample;
			uint32_t subchunk2ID;
			uint32_t subchunk2Size;
		};
#pragma pack(pop)


		typedef ALuint BufferID;
		typedef ALuint SourceID;


	}
	
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

	// File formats support: wav
	Types::BufferID LoadSoundFile(const std::string& filename) {

		std::ifstream file(filename, std::ios::binary);

		// WAV
		Types::WavHeaderInfo header{};
		file.read(reinterpret_cast<char*>(&header), sizeof(header));
		if (header.chunkID != 0x52494646 || header.format != 0x45564157) {
			file.close();
			return NULL;
		}
		// PCM
		if (header.audioFormat != 1) {
			return NULL;
		}
		
		std::vector<char> audioData(header.subchunk2Size);
		file.read(audioData.data(), header.subchunk2Size);
		file.close();

		ALenum format{};
		if (header.numChannels == 1 && header.bitsPerSample == 1) {
			format = AL_FORMAT_MONO8;
		}
		else if (header.numChannels == 1 && header.bitsPerSample == 2) {
			format = AL_FORMAT_MONO16;
		}
		else if (header.numChannels == 2 && header.bitsPerSample == 1) {
			format = AL_FORMAT_STEREO8;
		}
		else if (header.numChannels == 2 && header.bitsPerSample == 2) {
			format = AL_FORMAT_STEREO16;
		}
		else return NULL;

		Types::BufferID bufferID{};
		alGenBuffers(1, &bufferID);
		alBufferData(bufferID, format, &audioData, header.subchunk2Size, header.sampleRate);

		return bufferID;
	}

	void Play() {
		// ��Ҫ����һ�µ��� the source which was created by buffer Ӧ��Ӧ���ӵ����棬�������� Play...
	}
	
}

namespace Test {

	void test_main() {
		OpenAL::Types::BufferID new_sound = OpenAL::LoadSoundFile("test.wav");


	}
}