
#include "MyOverFlowException.h"

MyOverFlowException::MyOverFlowException(std::string const& _err,const std::string& _fileName,const std::string& _funcName,const std::string& _line)
:MyException(_err,_fileName ,_funcName , _line)
{

}
 