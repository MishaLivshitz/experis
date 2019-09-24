
#include "rational.h"
#include <iostream>
#include <cmath>
Rational::Rational()
:
m_numer(0),
m_denum(1)
{}

Rational::Rational(int _nominator)
:
m_numer(_nominator),
m_denum(1)
{}

Rational::Rational(int _nominator, int _denom)
:
m_numer(_nominator),
m_denum(_denom)
{}
//Operators

// mem-functions
// Public Operations
void Rational::print() const
{
	std::cout << "{" << m_numer << "/" << m_denum << "}";
}

void Rational::mul(int _num)
{
	m_numer *= _num;
}

void Rational::mul(Rational const & _rhs)
{
	mul(_rhs.m_numer);
	m_denum *= _rhs.m_denum;
}

void Rational::add(int _num)
{
	_num *= m_denum;
	m_numer += _num;
}

void Rational::add(Rational const & _rhs)
{
	m_numer = m_numer * _rhs.m_denum + _rhs.m_numer * m_denum;
	m_denum *= _rhs.m_denum; 
}

void Rational::sub(int _num)
{
	add(-_num);
}
void Rational::sub(Rational const & _rhs)
{
	m_numer = m_numer * _rhs.m_denum - _rhs.m_numer * m_denum;
	m_denum *= _rhs.m_denum; 
}

void Rational::div(int _num)
{
	m_denum *= _num;
}
void Rational::div(Rational const & _rhs)
{
	mul(_rhs.m_denum);
	m_denum *= _rhs.m_numer;
}

void Rational::reduce()
{
	int min = std::min(m_numer, m_denum);
	
	min = std::abs(min);	
	while(min>1)
	{
		if(0 == m_numer % min && 0 == m_denum % min)
		{
			m_numer /= min;
			m_denum /= min;
		}
		
		--min;
	}
}

int Rational::numerator()const
{
	return m_numer;
} 
int Rational::denumerator()const
{
	return m_denum;
} 
//Private operation

