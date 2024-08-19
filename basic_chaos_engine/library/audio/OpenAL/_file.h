#pragma once

#include "common_audio.h"

namespace basic_chaos_engine {
	// File formats support: wav
	type::BufferID LoadSoundFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::binary);
		// WAV
		type::WavHeaderInfo header{};
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

		type::BufferID bufferID{};
		alGenBuffers(1, &bufferID);
		alBufferData(bufferID, format, &audioData, header.subchunk2Size, header.sampleRate);
		return bufferID;
	}
}