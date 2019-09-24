#ifndef BASE_FUNCTOR_H
#define BASE_FUNCTOR_H


template<typename T>
class BaseFunctor
{
public:
    virtual ~BaseFunctor() {};
    virtual T operator()() const = 0;

};


#endif