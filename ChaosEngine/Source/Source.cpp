#pragma once



namespace Chaos {



    inline vec2<int> vecf2i(vec2<float>& vecf)
    {
        return vec2<int>(static_cast<int>(vecf.x), static_cast<int>(vecf.y));
    }



    inline vec3<int> vecf2i(vec3<float>& vecf)
    {
        return vec3<int>(static_cast<int>(vecf.x), static_cast<int>(vecf.y), static_cast<int>(vecf.z));
    }



    inline vec2<float> veci2f(vec2<int>& vecf)
    {
        return vec2<float>(static_cast<float>(vecf.x), static_cast<float>(vecf.y));
    }



    inline vec3<float> veci2f(vec3<int>& vecf)
    {
        return vec3<float>(static_cast<float>(vecf.x), static_cast<float>(vecf.y), static_cast<float>(vecf.z));
    }



}



// OpenAL
#include "ExternalLibrary/Audio/OpenAL/OpenAL.cpp"



// Base
#include "System.cpp"
#include "Base.cpp"
#include "Device.cpp"
#include "Resource.cpp"



// AudioX
#include "AudioX/AudioManager.cpp"
#include "AudioX/Sound.cpp"
#include "AudioX/Sample.cpp"
#include "AudioX/Channel.cpp"
#include "AudioX/ChannelGroup.cpp"
#include "AudioX/AudioPlayer.cpp"



// WindowX
#include "WindowX/WindowManager.cpp"
#include "WindowX/WindowProperty.cpp"
#include "WindowX/Window.cpp"
#include "WindowX/KeyStateBuffer.cpp"
#include "WindowX/Hotkey.cpp"



// GraphicX
#include "GraphicX/GraphicManager.cpp"
#include "GraphicX/Renderer.cpp"
#include "GraphicX/RenderTaskParam.cpp"
#include "GraphicX/Viewport.cpp"
#include "GraphicX/Texture.cpp"



// InternalDevice
#include "InternalDevice/Engine.cpp"
#include "InternalDevice/Stage.cpp"
#include "InternalDevice/Scene.cpp"



// PhysicX
#include "PhysicX/PhysicsEngine.cpp"



// GameObject
#include "GameObject/Actor.cpp"
