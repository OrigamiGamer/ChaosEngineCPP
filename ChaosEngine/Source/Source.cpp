#include "Class/Class.h"



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



// Log
#include "Source/Log/OutputStream.cpp"
#include "Source/Log/Logger.cpp"
#include "Source/Log/LoggerManager.cpp"



// Base
#include "Source/System.cpp"
#include "Source/Base.cpp"
#include "Source/Device.cpp"
#include "Source/Resource.cpp"



// AudioX
#include "Source/AudioX/AudioManager.cpp"
#include "Source/AudioX/Sound.cpp"
#include "Source/AudioX/Sample.cpp"
#include "Source/AudioX/Channel.cpp"
#include "Source/AudioX/ChannelGroup.cpp"
#include "Source/AudioX/AudioPlayer.cpp"



// WindowX
#include "Source/WindowX/WindowManager.cpp"
#include "Source/WindowX/WindowProperty.cpp"
#include "Source/WindowX/Window.cpp"
#include "Source/WindowX/KeyStateBuffer.cpp"
#include "Source/WindowX/Hotkey.cpp"



// GraphicX
#include "Source/GraphicX/GraphicManager.cpp"
#include "Source/GraphicX/Color.cpp"
#include "Source/GraphicX/Renderer.cpp"
#include "Source/GraphicX/RenderTaskParam.cpp"
#include "Source/GraphicX/Viewport.cpp"
#include "Source/GraphicX/Texture.cpp"



// InternalDevice
#include "Source/InternalDevice/Engine.cpp"
#include "Source/InternalDevice/Stage.cpp"
#include "Source/InternalDevice/Scene.cpp"



// PhysicX
#include "Source/PhysicX/PhysicsEngine.cpp"



// Component
#include "Source/Component/Timer.cpp"



// GameObject
#include "Source/GameObject/Actor.cpp"
