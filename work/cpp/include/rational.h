
#ifndef RATIONAL_H
#define RATIONAL_H
/**
 *	@file rational.h
 *
 *	@brief	Define rational number
 *
 */

class Rational {
public:
// CTOR
	Rational();
	Rational(int _numinator);
	Rational(int _numinator, int _denum);
// DTOR
//	~Rational();

// mem-functions
// Operations

	void print() const;
	void mul(int _num);
	void mul(Rational const & _rhs);
	
	void add(int _num);
	void add(Rational const & _rhs);
	
	void sub(int _num);
	void sub(Rational const & _rhs);
	
	void div(int _num);
	void div(Rational const & _rhs);
	
	void reduce();
	
	int numerator() const;
	int denumerator() const;
	
	
// Data members
private:
	int	m_numer;
	int	m_denum;
};

#endif // RATIONAL_H
