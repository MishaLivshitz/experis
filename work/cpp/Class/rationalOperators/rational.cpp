
#include "Rational.h"
#include <iostream>
#include <cmath>
Rational::Rational(int _nominator, int _denom)
:
m_numer(_nominator),
m_denom(_denom)
{
}


Rational& Rational::operator+= (Rational const& _rhs)
{
	add(_rhs);
	return *this;
}

Rational& Rational::operator-= (Rational const& _rhs)
{
	sub(_rhs);
	return *this;
}
Rational& Rational::operator*= (Rational const& _rhs)
{
	mul(_rhs);
	return *this;
}
Rational& Rational::operator/= (Rational const& _rhs)
{
	div(_rhs);
	return *this;
}

Rational operator+(Rational const& _lhs, Rational const& _rhs)
{
	Rational res(_lhs);
	res.add(_rhs);
	
	return res;
}

Rational operator-(Rational const& _lhs, Rational const& _rhs)
{
	Rational res(_lhs);
	res.sub(_rhs);
	
	return res;
}
Rational operator*(Rational const& _lhs, Rational const& _rhs)
{
	Rational res(_lhs);
	res.mul(_rhs);
	
	return res;
}
Rational operator/(Rational const& _lhs, Rational const& _rhs)
{
	Rational res(_lhs);
	res.div(_rhs);
	
	return res;
}

// mem-functions
// Public Operations
void Rational::print(std::ostream& _os) const
{
	_os << "{" << m_numer << "/" << m_denom << "}";
}

void Rational::mul(int _num)
{
	m_numer *= _num;
}

void Rational::mul(Rational const & _rhs)
{
	mul(_rhs.m_numer);
	m_denom *= _rhs.m_denom;
}

void Rational::add(int _num)
{
	_num *= m_denom;
	m_numer += _num;
}

void Rational::add(Rational const & _rhs)
{
	m_numer = m_numer * _rhs.m_denom + _rhs.m_numer * m_denom;
	m_denom *= _rhs.m_denom; 
}

void Rational::sub(int _num)
{
	add(-_num);
}
void Rational::sub(Rational const & _rhs)
{
	m_numer = m_numer * _rhs.m_denom - _rhs.m_numer * m_denom;
	m_denom *= _rhs.m_denom; 
}

void Rational::div(int _num)
{
	m_denom *= _num;
}
void Rational::div(Rational const & _rhs)
{
	mul(_rhs.m_denom);
	m_denom *= _rhs.m_numer;
}

void Rational::reduce()
{
	int min = std::min(m_numer, m_denom);
	
	min = std::abs(min);	
	while(min>1)
	{
		if(0 == m_numer % min && 0 == m_denom % min)
		{
			m_numer /= min;
			m_denom /= min;
		}
		
		--min;
	}
}

int Rational::numerator()const
{
	return m_numer;
} 
int Rational::denominator()const
{
	return m_denom;
} 
//Private operation

