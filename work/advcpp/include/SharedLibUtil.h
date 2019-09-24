#ifndef SHARED_LIB_H
#define SHARED_LIB_H


#include "utils.h"
#include "MyException.h"

namespace advcpp{

class SharedLibUtil
{

public:

    SharedLibUtil(char const* a_libName) throw(MyException);
    void close();
    void* getPtr(char const* a_name) const throw(MyException);

private:
    void* m_handle;
    
};

}// advcpp
#endif