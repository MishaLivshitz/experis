
#include <stdexcept>

class MyUnderFlowException: public std::underflow_error
{
public:
    MyUnderFlowException(std::string const& _err,const std::string& _fileName,const std::string& _funcName,const std::string& _line);

};