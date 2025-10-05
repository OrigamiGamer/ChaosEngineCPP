#pragma once

#include "Class/InternalDevice/InternalDevice.h"



namespace Chaos::InternalDevice {



    // Please initialize Scene before inheriting it.
    class Scene : public Base {
    public:
        Stage* stage = nullptr;
        std::vector<GameObject::Actor*> actors;
        std::vector<ActorMessage> actorMessages;

        Scene(std::string new_sceneName);

        // A callback method of scene, calling while updating.
        // 场景更新时的回调方法。
        virtual void update();

        // A callback method of scene, calling after having switched from another scene.
        // 从另一场景切换到此场景后的回调方法。
        virtual void onEntered();

        // A callback method of scene, calling while exiting. This action will finish while returned value is "true".
        // 场景退出时的回调方法。当返回值为 "true" 时该行为完成。
        virtual bool onExiting();

        // A callback method of scene, calling while hot-key is pressed.
        // @param virtualKey The virtual key code of hot-key pressed.
        // 热键被按下时的回调方法。
        virtual void onHotkeyPressed(int virtualKey);

        // A callback method of scene, calling while hot-key is pressed.
        // @param name The name of hot-key pressed.
        // 热键被按下时的回调方法。
        virtual void onHotkeyPressed(std::string hotkeyName);

        // A callback method of scene, calling while hot-key is released.
        // @param virtualKey The virtual key code of hot-key released.
        // 热键被释放时的回调方法。
        virtual void onHotkeyReleased(int virtualKey);

        // A callback method of scene, calling while hot-key is released.
        // @param name The name of hot-key released.
        // 热键被释放时的回调方法。
        virtual void onHotkeyReleased(std::string hotkeyName);

        void registerActor(GameObject::Actor* new_actor);

        bool dispatchMessage(ActorMessage& message);
        // bool sendMessage(std::string actorType, std::string actorName, std::string message);
        // bool sendMessage(GameObject::Actor* actor, std::string message);

    };



}