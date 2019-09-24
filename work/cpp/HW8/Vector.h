#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>
#include <string>


template <typename T>
class Vector: public std::vector<T>
{

typedef typename std::vector<T> Base;

public:
        typedef typename Base::const_iterator const_iterator;
        //CTOR
        Vector();
        //CCTOR
        Vector(Vector const&);
        //DTOR
        ~Vector();
        //Assignment operator
        Vector& operator=(Vector const& _rhs);
        void print(std::ostream& _os) const;


        const_iterator cbegin() const;
        const_iterator cend() const;
        const std::string& type() const;

protected:
        void setType(std::string const& _type);

protected:
        std::string m_type;

public:
        static const std::string s_TYPE;

};

//CTOR
template <typename T>
Vector<T>::Vector()
:Base()
,m_type(s_TYPE)
{
}

//CCTOR
template <typename T>
Vector<T>::Vector(Vector const& _rhs)
:Base(_rhs)
,m_type(s_TYPE)
{
}

//DTOR
template <typename T>
Vector<T>::~Vector()
{
    setType(s_TYPE);
    std::cout << s_TYPE << " destructor\n";
}
//Assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(Vector const& _rhs)
{
    Base::operator= (_rhs);
    return *this;
}

//static initializers
template <typename T>
std::string const Vector<T>::s_TYPE = "Vector";


//public funcs
template<typename T>
void Vector<T>::print(std::ostream& a_os) const
{
    const_iterator itrBegin = cbegin();
    const_iterator itrEnd = cend();

    a_os << "[";

    for(;itrBegin!=itrEnd-1;++itrBegin)
    {
        a_os << *itrBegin << ",";
    }

    a_os << *itrBegin<< "]\n";
}

template<typename T>
void Vector<T>::setType(std::string const& _type)
{
    m_type = _type;
}

template<typename T>
const std::string& Vector<T>::type() const
{
    return m_type;
}

template<typename T>
inline typename Vector<T>::const_iterator Vector<T>::cbegin() const
{
    return Base::begin();
}

template<typename T>
inline typename Vector<T>::const_iterator Vector<T>::cend() const
{
    return Base::end();
}

//Global funcs
template<typename T>
std::ostream& operator<< (std::ostream& a_os ,Vector<T> const& a_sVec)
{
    a_sVec.print(a_os);
    return a_os;
}


#endif