#ifndef RATIONAL_CLASS_H
#define RATIONAL_CLASS_H


#include <iostream>

class Rational
{
public:
	Rational(int _numer = 0, int _denom = 1);

	int numerator() const;
	int denominator() const;

	void print(std::ostream& _os) const;

	void reduce();

	void mul(int _numer);
	void mul(Rational const& _rational);

	void add(int _numer);
	void add(Rational const& _rational);

	void sub(int _numer);
	void sub(Rational const& _rational);
	
	void div(int _num);
	void div(Rational const & _rhs);

	// Operators
	Rational& operator+= (Rational const& _rhs);
	Rational& operator-= (Rational const& _rhs);
	Rational& operator*= (Rational const& _rhs);
	Rational& operator/= (Rational const& _rhs);
	
private:
	int		m_numer;
	int		m_denom;
};

Rational operator+(Rational const& _lhs, Rational const& _rhs);

std::ostream& operator<<(std::ostream& _os, Rational const& _rational);



#endif // RATIONAL_CLASS_H
