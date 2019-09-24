
#include <stdexcept>

class MyBadArgumentException: public std::invalid_argument
{
public:
    MyBadArgumentException(std::string const& _err,const std::string& _fileName,const std::string& _funcName,const std::string& _line);

    


};