
#include "MyBadArgumentException.h"

MyBadArgumentException::MyBadArgumentException(std::string const& _err,const std::string& _fileName,const std::string& _funcName,const std::string& _line)
:std::invalid_argument(_err + ":\nerror at:\nFile:" + _fileName + "\nFunction:" +_funcName +"\nLine: " + _line + "\n")
{

}