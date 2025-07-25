#pragma once



#include "ChaosEngine.h"



namespace Chaos::AudioX {



    class AudioManager : public Base {
    public:
        AudioManager(InternalDevice::Engine* new_engine);
        ~AudioManager();
    };



    class Sound : public Resource {
    public:
        Sound(InternalDevice::Engine* new_engine);
        ~Sound();
    };



    class Sample : public Resource {
    public:
        Sample(InternalDevice::Engine* new_engine);
        ~Sample();
    };



    class Channel : public Resource {
    public:
        Channel(InternalDevice::Engine* new_engine);
        ~Channel();
    };



    class ChannelGroup : public Resource {
    public:
        ChannelGroup(InternalDevice::Engine* new_engine);
        ~ChannelGroup();
    };



    class AudioPlayer : public Base {
    public:
        AudioPlayer(InternalDevice::Engine* new_engine);
        ~AudioPlayer();
    };



}
