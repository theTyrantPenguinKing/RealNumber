#ifndef REALNUMBER_HPP
#define REALNUMBER_HPP

#include <iostream>
#include <string>
#include <deque>
#include <cinttypes>
#include <iterator>
#include <cctype>

class RealNumber{
	friend std::ostream& operator<<(std::ostream&, const RealNumber&);
	
	friend std::istream& operator>>(std::istream&, RealNumber&);
	
	// equality overloads
	friend bool operator==(const std::int64_t, const RealNumber&);
	friend bool operator==(const std::string&, const RealNumber&);
	
	// inequality overloads
	friend bool operator!=(const std::int64_t, const RealNumber&);
	friend bool operator!=(const std::string&, const RealNumber&);
	
	// less than overloads
	friend bool operator<(const std::int64_t, const RealNumber&);
	friend bool operator<(const std::string&, const RealNumber&);
	
	// less than or equal overloads
	friend bool operator<=(const std::int64_t, const RealNumber&);
	friend bool operator<=(const std::string&, const RealNumber&);
	
	// greater than overloads
	friend bool operator>(const std::int64_t, const RealNumber&);
	friend bool operator>(const std::string&, const RealNumber&);
	
	// greater than or equal overloads
	friend bool operator>=(const std::int64_t, const RealNumber&);
	friend bool operator>=(const std::string&, const RealNumber&);
	
	private:
		std::deque<std::uint16_t> digits;
		std::int16_t sign;
		std::size_t precision;	// amount of digits after decimal point
		
		// removes unneeded zeros
		void trim();
		
		/*
		Compares the numbers ignoring their signs
		
		Returns 1 if the first number is greater than the second,
		0 if they are equal, and -1 if the first is less than the
		second
		*/
		static std::int16_t compare(const RealNumber&, const RealNumber&);
		
		/* return the addition of the numbers
		
		PRE: the numbers have the same precision
		*/
		static RealNumber addition(const RealNumber&, const RealNumber&);
		
		/* returns the subtraction of the numbers
		
		PRE: the absolute value of the first number is greater than or equal
		to the absolute value of the second number and have the same precision
		*/
		static RealNumber subtraction(const RealNumber&, const RealNumber&);
		
	public:
		RealNumber();
		RealNumber(const std::int64_t);
		RealNumber(const std::string&);
		RealNumber(const RealNumber&);
		
		~RealNumber();
		
		// assignment overloads
		const RealNumber& operator=(const std::int64_t);
		const RealNumber& operator=(const std::string&);
		const RealNumber& operator=(const RealNumber&);
		
		// returns the amount of digits before the decimal point
		std::size_t getMantissa() const ;
		
		// returns the amout of digits after the decimal point
		std::size_t getPrecision() const ;
		
		// equality overload
		bool operator==(const RealNumber&) const ;
		
		// inequality overload
		bool operator!=(const RealNumber&) const ;
		
		// less than overload
		bool operator<(const RealNumber&) const ;
		
		// less than or equal overload
		bool operator<=(const RealNumber&) const ;
		
		// greater than overload
		bool operator>(const RealNumber&) const ;
		
		// greater than or equal overload
		bool operator>=(const RealNumber&) const ;
		
		// returns the opposite of the number
		RealNumber operator-() const ;
		
		// returns the sum of the two numbers
		RealNumber operator+(const RealNumber&) const ;
		
		// returns the subtraction of the two numbers
		RealNumber operator-(const RealNumber&) const ;
};

#endif
