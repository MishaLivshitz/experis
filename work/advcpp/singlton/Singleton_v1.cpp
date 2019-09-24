#include "Singleton_v1.h"
#include <iostream>
namespace advcpp{


Singleton_v1* Singleton_v1::s_instance = 0;
AtomicVal<char> Singleton_v1::s_first;
AtomicVal<char> Singleton_v1::s_done;

Singleton_v1::Singleton_v1()
{

}

Singleton_v1& Singleton_v1::getInstance()
{
    
    if(!s_done)
    {
        if(!s_first.testAndSet(1))
        {
            s_instance = new Singleton_v1;
            s_done += 1;
        }
        else
        {
            while(!s_done.value())
            {

            }
        }
    }


    return *s_instance;
}

} //advcpp