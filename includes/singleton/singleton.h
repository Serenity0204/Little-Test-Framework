#ifndef SINGLETON_H
#define SINGLETON_H

#pragma once

namespace LTF
{
    template <class T>
    class Singleton
    {
    private:
        Singleton() = delete;
        ~Singleton() = delete;
        Singleton(const Singleton<T>& rhs) = delete;
        Singleton<T>& operator=(const Singleton<T>& rhs) = delete;

    private:
        static T* s_instance;

    public:
        inline static void destroy()
        {
            if (Singleton<T>::s_instance == nullptr) return;
            delete Singleton<T>::s_instance;
        }

        inline static T* instance()
        {
            if (Singleton<T>::s_instance == nullptr) Singleton<T>::s_instance = new T();
            return Singleton<T>::s_instance;
        }
    };

    template <class T>
    T* Singleton<T>::s_instance = nullptr;
};

#endif // SINGLETON_H
