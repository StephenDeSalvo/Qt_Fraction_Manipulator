#ifndef FRACTION_H
#define FRACTION_H

/** @file Fraction.h
	@brief Stores the Fraction class

	This is the class definition for the Fraction class that uses int / int.
*/

#include <iostream>
#include <string>

using namespace std;

/** @class Fraction
	@brief stores int/int

	Implements numerical operators and simplifies to reduced form.
*/
class Fraction {
public:

	// Constructors
	Fraction();
	Fraction(int input_numerator);
	Fraction(int input_numerator, int input_denominator);

	//Fraction& plusEquals(const Fraction& rhs);

	// Arithmetic operators
	Fraction& operator+=(const Fraction& rhs);
	Fraction& operator*=(const Fraction& rhs);
	Fraction operator-();
	Fraction operator+();

	// Increment operators
	Fraction& operator++();
	Fraction operator++(int);

	// A few comparisons
	friend bool operator<(const Fraction& lhs, const Fraction& rhs);
	friend bool operator==(const Fraction& lhs, const Fraction& rhs);

	// operator[] only accepts ONE argument.
	int operator[](string&);
	int operator[](int);

	// operator() can have 0, 1, 2, etc., arguments
	void operator()();
	int operator()(int, int);
	int operator()(int, int, const string&, double);

	//operator double();

	/** Output operator

	// cout << f ;
	// operator<<( cout, f);
	// cout << f << endl;
	// Return parameter allows for operator chaining.

		@param out is the output stream
		@param f is the Fraction object
		@returns the output stream for chaining
		*/
	friend ostream& operator<<(ostream& out, const Fraction& f) {
		out << f.numerator << "/" << f.denominator;
		return out;
	}

	/** ... */
	friend istream& operator>>(istream& in, Fraction& a) {
	int num, denom;
	in>>num; // Gets the numerator of the fraction
	
	char c;
	//in>>c    // ? Your book has this line, which doesn’t work very well in all formats.
	c = in.get(); // Gets the next character, it might be a ‘/’
	
	// After getting first int, test whether / was input next
	if(c == '/')
		in>>denom;
	else {
		in.unget();
		denom = 1;
	}
//	a = Fraction(num, denom);
	a.numerator = num;
	a.denominator = denom;
	return in;
}



	// Real answer is don't define this operator in the first place.
	// Only for demonstration purposes.
	operator string();
	
	// Print the fraction
	void print();
private:
	int numerator;
	int denominator;

	void Reduce();

};

// non-member arithmetic
//inline Fraction operator+(Fraction lhs, const Fraction& rhs) { return lhs += rhs; };
Fraction operator+(Fraction lhs, const Fraction& rhs);
Fraction operator*(Fraction lhs, const Fraction& rhs);

/*
inline Fraction operator+(Fraction lhs, int rhs) {
	Fraction c(rhs);
	return lhs+c;
}
*/

// non-member comparison
bool operator!=(const Fraction& lhs, const Fraction& rhs);
bool operator<=(const Fraction& lhs, const Fraction& rhs);
bool operator>=(const Fraction& lhs, const Fraction& rhs);
bool operator>(const Fraction& lhs, const Fraction& rhs);




#endif