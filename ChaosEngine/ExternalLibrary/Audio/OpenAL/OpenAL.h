#pragma once



// STL

#include <vector>
#include <string>



// libsndfile

#include "ExternalLibrary/Audio/libsndfile/sndfile.h"



// openal

#include "ExternalLibrary/Audio/OpenAL/raw/al.h"
#include "ExternalLibrary/Audio/OpenAL/raw/alc.h"



// ----------------
// 1st-declarations
// ----------------

namespace OpenAL {

    class Source;

    class AudioPlayer;

    class Buffer;

    class AudioEngine;

}



// ----------------
// 2nd-declarations
// ----------------

namespace OpenAL {



    class AudioEngine {
    private:
        ALCdevice* _device = nullptr;

    public:
        std::vector<AudioPlayer*> audioPlayers;

        AudioEngine();

        int getLastError();

        bool initialize();

        bool release();

        AudioPlayer* createAudioPlayer(std::string new_playerName = "");

        friend class Buffer;
        friend class AudioPlayer;
        friend class Source;
    };



    class AudioPlayer {
    private:
        AudioEngine* _audioEngine = nullptr;
        ALCcontext* _context = nullptr;

        inline bool _makeCurrent();

        bool _initialize();

        bool _release();

    public:
        std::string name;
        std::vector<Buffer*> buffers;
        std::vector<Source*> sources;

        AudioPlayer();

        // @param filename The absolute path to an audio file.
        Buffer* loadAudioFile(std::string filename, std::string new_bufferName = "");

        Source* createSource(std::string new_sourceName = "");

        bool playSource(Source* source);
        bool playSource(std::string sourceName);

        friend class AudioEngine;
        friend class Buffer;
        friend class Source;
    };



    class Buffer {
    private:
        AudioPlayer* _audioPlayer = nullptr;
        ALuint _bufferID = 0;

    public:
        std::string name;

        Buffer();

        friend class AudioEngine;
        friend class AudioPlayer;
        friend class Source;
    };



    class Source {
    private:
        AudioPlayer* _audioPlayer = nullptr;
        ALuint _sourceID = 0;

        inline bool _makeCurrent();

    public:
        std::string name;

        Source();

        bool pushBuffer(Buffer* new_buffer);
        bool pushBuffer(std::string bufferName);

        // Play, replay, or resume this source.
        bool play();

        bool setVolume(float new_volume);

        bool setPositionOffset(int new_position);

        // @param new_time Units: seconds
        bool setTimeOffset(float new_time);

        friend class AudioEngine;
        friend class Buffer;
        friend class AudioPlayer;
    };



}
