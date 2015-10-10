/** @file Fraction.cpp
	@brief The implementation for Fraction class

	...
*/

#include "Fraction.h"


/** Default constructor initializes the fraction to 0/1.

    numerator and denominator are default initialized
	THEN it runs the code inside { ... }
*/
Fraction::Fraction() {
	numerator = 0;
	denominator = 1;
}

/** Initializes fraction to input_numerator/1
	@param input_numerator this is the value of the numerator
*/
Fraction::Fraction(int input_numerator) : numerator(input_numerator), denominator(1) {

}

/** Initializes fraction to input_numerator/input_denominator
	@param input_numerator is the initial numerator
	@param input_denominator is the initial denominator
*/
Fraction::Fraction(int input_numerator, int input_denominator) : numerator(input_numerator), denominator(input_denominator) {
	Reduce();
}

/** Prints out the fraction in the form n/d */
void Fraction::print() {
	cout << numerator << "/" << denominator;
}

/** Performs f += rhs where f is the object calling the function
	@param rhs is the Fraction object to add to f
*/
/*Fraction& Fraction::plusEquals(const Fraction& rhs) {
	// a/b + c/d = (a*d+b*c) / (b*d)
	int a = numerator;
	int b = denominator;
	int c = rhs.numerator;
	int d = rhs.denominator;

	numerator = (a*d+b*c);
	denominator = (b*d);

	return *this;
};
*/

/** ... */
Fraction& Fraction::operator+=(const Fraction& rhs) {
	// a/b + c/d = (a*d+b*c) / (b*d)
	int a = numerator;
	int b = denominator;
	int c = rhs.numerator;
	int d = rhs.denominator;

	numerator = (a*d+b*c);
	denominator = (b*d);

	Reduce();
	return *this;
}


/** ...
..
..
*/
Fraction& Fraction::operator*=(const Fraction& rhs) {
	// a/b * c/d = (a*c) / (b*d)
	int a = numerator;
	int b = denominator;
	int c = rhs.numerator;
	int d = rhs.denominator;

	numerator   = (a*c);
	denominator = (b*d);

	Reduce();
	return *this;
}

/** Critical assumption that b > 0, i.e., denominator is always positive */
inline Fraction& Fraction::operator++() {
	// a/b + 1 = a/b + b/b = (a+b) / b
	numerator += denominator;

	// Maybe we don't need this...we shall ask a number theorist!
	Reduce();
	return *this;
}

Fraction Fraction::operator++(int unused) {
	
	// These two are the same, they construct the object with initial values 
	// provided by *this
	Fraction clone( *this );
	//Fraction clone = *this;

	// This one would be different, not desireable
	//Fraction clone;  // Construct object first by default
	//clone = *this;   // Assign values from existing object

	// These three do the same thing.
	//++*this;
	this->operator++();
	//(*this).operator++();

	return clone;
}



/** performs lhs+rhs fraction arithmetic
	@param lhs is the left hand side of the addition
	@param rhs is the right hand side of the addition
	@returns the value of lhs+rhs. 
*/
Fraction operator+(Fraction lhs, const Fraction& rhs) { return lhs+=rhs; }

/** ... */
Fraction operator*(Fraction lhs, const Fraction& rhs) {
	return lhs*=rhs;
}

/** ... */
Fraction Fraction::operator-() {
	Fraction negation( -numerator, denominator);

	// This operation preserves reduced form.  No need to call Reduce().
	return negation;
}

/** Called using Fraction p;   +p; */
Fraction Fraction::operator+() {
	Fraction copy(*this);
	return copy;
}


/** ... */
bool operator<(const Fraction& lhs, const Fraction& rhs) {
	// a/b < c/d ?
	// First approach: convert to doubles
	//double left = static_cast<double>(lhs.numerator)/lhs.denominator;
	//double right = static_cast<double>(rhs.numerator)/rhs.denominator;

	// Second approach: assume denominators are always > 0.
	// return a*d < b*c
	int a = lhs.numerator;
	int b = lhs.denominator;
	int c = rhs.numerator;
	int d = rhs.denominator;


	return a*d < b*c;
}

/** ... */
bool operator==(const Fraction& lhs, const Fraction& rhs) {
	// a/b = c/d

	// First approach: Cross multiply
	// a*d = b*c
	//return ( lhs.numerator*rhs.denominator == lhs.denominator*rhs.numerator);

	// Second approach: assume fractions are in reduced form, compare numerators
	// and denominators directly.
	return ( lhs.numerator == rhs.numerator && rhs.denominator == lhs.denominator);

}

/** ... */
bool operator!=(const Fraction& lhs, const Fraction& rhs) {
	return !(lhs==rhs);
}

/** ... */
bool operator<=(const Fraction& lhs, const Fraction& rhs) {
	return (lhs < rhs) || (lhs == rhs);
}

/** ... */
bool operator>=(const Fraction& lhs, const Fraction& rhs) {
	return !(lhs<rhs);
}

/** ... */
bool operator>(const Fraction& lhs, const Fraction& rhs) {
	// Exercise...think about this one.
	return true;
}



/** Calculates the greatest common divisor of integers a and b.
	@param a is one of the values
	@param b is the second value
	@return gcd(a,b)
*/
int gcd(int a, int b) {

	int t = 0;

	// loop until reduction is finished
	while (b != 0) {
       t = b;
       b = a % b;
       a = t;
	}
    return a;
}


/** This reduces the fraction to lowest terms: \n
	1.  5/5  --> 1/1
	2.  0/a  --> 0/1  (assuming a != 0)
	3.  0/0  --> Error?
	4.  2/4  --> 1/2
	5.  -3/-5--> 3/5
	6.  2/-7 --> -2/7
	7.  a/0  --> Error?
*/
void Fraction::Reduce() {

	// GCD algorithm:
	int division_factor = gcd(numerator,denominator);

	// e.g., 15/5, division_factor = 5;
	// Now divide numeratror and denominator by division_factor

	numerator /= division_factor;
	denominator /= division_factor;


	// a/b, -a/b, a/-b, -a/-b

	// a/-b  OR  -a/-b
//	if( (numerator >0 && denominator<0) || (numerator<0 && denominator < 0) ) {
	// Equivalent to
	if( denominator<0 ) {
		//numerator =- numerator; // not recommended, possible confusion with -=
		numerator *= -1;
		denominator *= -1;
	}

	
//	cout << numerator << "/"<<denominator<<endl;

}

/* // Not necessary once you properly #include <string>
bool operator==(const string& lhs, const string& rhs) {

	for(size_t i=0;i<lhs.size();i++) {
		if(lhs[i] != rhs[i])
			return 0;
	}

	return 1;
}
*/
int Fraction::operator[](string& value) {


	if( value == string("numerator"))
		return numerator;
	else if(value == string("denominator") )
		return denominator;
	else
		return -12345;

}
	

int Fraction::operator[](int value) {
	if( value == 0)
		return numerator;
	else if(value == 1)
		return denominator;
	else
		return -12345;

}


void Fraction::operator()() {
	numerator = 0;
	denominator = 1;

}

//int operator()(int, int);
	
int Fraction::operator()(int a, int b, const string& message, double d) {

	cout << a << "/"<<b<<endl;
	if(message == "monkey")
		cout << "no monkey business here."<<endl;

	cout<<d<<endl;

	return static_cast<int>(d);
}


//Fraction::operator double() {
//	return static_cast<double>(numerator)/denominator;
//}

Fraction::operator string() {
	return string("conversion to string");
}
