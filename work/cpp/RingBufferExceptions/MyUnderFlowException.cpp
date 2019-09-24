
#include "MyUnderFlowException.h"

MyUnderFlowException::MyUnderFlowException(std::string const& _err,const std::string& _fileName,const std::string& _funcName,const std::string& _line)
:std::underflow_error(_err + ":\nerror at:\nFile:" + _fileName + "\nFunction:" +_funcName +"\nLine: " + _line + "\n")
{

}