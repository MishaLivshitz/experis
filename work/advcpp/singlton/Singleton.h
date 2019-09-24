#ifndef SINGLETON_H
#define SINGLETON_H

namespace advcpp{

template <typename T>
class Singleton
{

public:
    static T& getInstance();

private:
    static T* s_instance;

private:
    Singleton();
    Singleton(Singleton const&);
    Singleton& operator=(Singleton const&);

};

template <typename T>
T* Singleton<T>::s_instance = new T;

template <typename T>
Singleton<T>::Singleton()
{
}

template <typename T>
T& Singleton<T>::getInstance()
{
    return *s_instance;
}











}//advcpp





#endif //SINGLETON_H