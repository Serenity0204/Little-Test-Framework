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

    public:
        // the only allowed access point
        inline static T& instance()
        {
            static T s_instance;
            return s_instance;
        }
    };
};

#endif // SINGLETON_H
