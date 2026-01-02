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



// Audio
#include "Source/Audio/AudioManager.cpp"
#include "Source/Audio/Sound.cpp"
#include "Source/Audio/Sample.cpp"
#include "Source/Audio/Channel.cpp"
#include "Source/Audio/ChannelGroup.cpp"
#include "Source/Audio/AudioPlayer.cpp"



// WindowX
#include "Source/WindowX/WindowManager.cpp"
#include "Source/WindowX/WindowProperty.cpp"
#include "Source/WindowX/Window.cpp"
#include "Source/WindowX/KeyStateBuffer.cpp"
#include "Source/WindowX/Hotkey.cpp"



// Graphics
#include "Source/Graphics/GraphicManager.cpp"
#include "Source/Graphics/Color.cpp"
#include "Source/Graphics/Renderer.cpp"
#include "Source/Graphics/RenderTaskParam.cpp"
#include "Source/Graphics/Viewport.cpp"
#include "Source/Graphics/Texture.cpp"



// InternalDevice
#include "Source/InternalDevice/Engine.cpp"
#include "Source/InternalDevice/Stage.cpp"
#include "Source/InternalDevice/Scene.cpp"



// Physic
#include "Source/Physics/PhysicsEngine.cpp"



// Component
#include "Source/Component/Timer.cpp"



// GameObject
#include "Source/GameObject/Actor.cpp"
