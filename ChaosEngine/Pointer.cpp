#pragma once

#include "Common.h"

namespace Chaos {

    // shared_ptr

    template<typename T>
    shared_ptr<T>::shared_ptr(T* new_p)
    {
        p = new_p;
    }

    template<typename T>
    shared_ptr<T>::~shared_ptr()
    {
        // std::cout << "do_nothing -> " << std::string(typeid(*this).name()) << std::endl;
    }

    template<typename T>
    inline bool shared_ptr<T>::has_value()
    {
        return p != nullptr;
    }

    template<typename T>
    inline T* shared_ptr<T>::get()
    {
        if (has_value()) return p;
        return nullptr;
    }

    template<typename T>
    inline T* shared_ptr<T>::operator->()
    {
        return this->get();
    }

    template<typename T>
    inline shared_ptr<T>& shared_ptr<T>::refer(T* new_p)
    {
        this->p = new_p;
        return *this;
    }

    template<typename T>
    inline shared_ptr<T>& shared_ptr<T>::refer(shared_ptr<T>& new_p)
    {
        this->p = new_p.get();
        return *this;
    }

    template<typename T>
    inline shared_ptr<T>& shared_ptr<T>::operator=(T* new_p)
    {
        return this->refer(new_p);
    }

    template<typename T>
    inline shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>& new_p)
    {
        return this->refer(new_p);
    }

    // ptr

    template<typename T>
    ptr<T>::ptr(T* new_p)
    {
        this->set(new_p);
    }

    template<typename T>
    ptr<T>::~ptr()
    {
        std::cout << "[CALL] ptr -> ~ptr()" << std::endl;
        this->release();
    }

    template<typename T>
    inline void ptr<T>::release()
    {
        std::cout << "[CALL] ptr -> release() | " << (shared_ptr<T>::has_value() == true ? "has_value" : "nullptr") << std::endl;
        if (shared_ptr<T>::has_value()) {
            delete shared_ptr<T>::p;
            shared_ptr<T>::p = nullptr;  // ??
        };
    }

    template<typename T>
    inline ptr<T>& ptr<T>::set(T* new_p)
    {
        if (shared_ptr<T>::has_value()) this->release();    // if it's better to do nothing ?
        shared_ptr<T>::p = new_p;
        return *this;
    }

    template<typename T>
    inline void ptr<T>::operator=(T* new_p)
    {
        this->set(new_p);
    }
}