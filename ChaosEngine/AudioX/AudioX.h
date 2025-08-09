#pragma once



#include "ChaosEngine.h"



namespace Chaos::AudioX {



    class AudioManager : public Base {
    public:
        AudioManager();
        ~AudioManager();
    };



    class Sound : public Resource {
    public:
        

        Sound();
        ~Sound();
    };



    class Sample : public Resource {
    public:
        Sample();
        ~Sample();
    };



    class Channel : public Resource {
    public:
        Channel();
        ~Channel();
    };



    class ChannelGroup : public Resource {
    public:
        ChannelGroup();
        ~ChannelGroup();
    };



    class AudioPlayer : public Base {
    public:
        AudioPlayer();
        ~AudioPlayer();
    };



}
