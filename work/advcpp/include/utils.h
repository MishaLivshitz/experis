#ifndef UTILS_H
#define UTILS_H


namespace advcpp{

class UnCopyable
{
public:
    UnCopyable() {};

private:
    UnCopyable( UnCopyable const& _rhs);
    UnCopyable& operator=(UnCopyable const& _rhs);

};


} //advcpp

#endif