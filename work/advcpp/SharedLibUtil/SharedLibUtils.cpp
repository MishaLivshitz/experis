#include "SharedLibUtil.h"
#include <dlfcn.h>
#include <sstream>

namespace advcpp
{

SharedLibUtil::SharedLibUtil(char const* a_libName) throw(MyException)
{
    dlerror();
    m_handle = dlopen(a_libName, RTLD_LAZY);
    if(0 == m_handle)
    {
        throw EXCEPTION(MyException, dlerror());
    }
 
}

void* SharedLibUtil::getPtr(char const* a_sym) const throw(MyException)
{
    dlerror();
    void* resPtr = dlsym(m_handle, a_sym);

    if(0 == resPtr)
    {
        throw EXCEPTION(MyException, dlerror());
    }

    return resPtr;
}

}