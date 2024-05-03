#pragma once
#include "OpenAL.h"

namespace OpenAL {

	namespace Type {

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

	// File formats support: wav
	Type::BufferID LoadSoundFile(const std::string& filename) {

		std::ifstream file(filename, std::ios::binary);

		// WAV
		Type::WavHeaderInfo header{};
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

		Type::BufferID bufferID{};
		alGenBuffers(1, &bufferID);
		alBufferData(bufferID, format, &audioData, header.subchunk2Size, header.sampleRate);

		return bufferID;
	}


}