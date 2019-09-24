#ifndef SINGLETON_V1_H
#define SINGLETON_V1_H
#include "utils.h"
#include "AtomicVal.h"

namespace advcpp{

class Singleton_v1: private UnCopyable
{

public:
    static Singleton_v1& getInstance();
   
private:
    static Singleton_v1* s_instance;
    static AtomicVal<char> s_first;
    static AtomicVal<char> s_done;
 
private:
    Singleton_v1();
    ~Singleton_v1();
};

}//advcpp





#endif //SINGLETON_V1_H