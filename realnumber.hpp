#ifndef REALNUMBER_HPP
#define REALNUMBER_HPP

#include <iostream>
#include <string>
#include <deque>
#include <cinttypes>
#include <iterator>
#include <cctype>

#include "rn_utils.hpp"

class RealNumber{
	// input/output overload
	friend std::ostream& operator<<(std::ostream&, const RealNumber&);
	friend std::istream& operator>>(std::istream&, RealNumber&);
	
	// relational operators overloads
	friend bool operator==(const std::int64_t, const RealNumber&);
	friend bool operator==(const std::string&, const RealNumber&);
	friend bool operator!=(const std::int64_t, const RealNumber&);
	friend bool operator!=(const std::string&, const RealNumber&);
	friend bool operator<(const std::int64_t, const RealNumber&);
	friend bool operator<(const std::string&, const RealNumber&);
	friend bool operator>(const std::int64_t, const RealNumber&);
	friend bool operator>(const std::string&, const RealNumber&);
	friend bool operator<=(const std::int64_t, const RealNumber&);
	friend bool operator<=(const std::string&, const RealNumber&);
	friend bool operator>=(const std::int64_t, const RealNumber&);
	friend bool operator>=(const std::string&, const RealNumber&);
	
	private:
		// deque containing the digits of the number
		std::deque<std::int16_t> digits;
		// sign of the number
		std::int16_t sign;
		// amount of digits after the decimal point
		std::size_t precision;
		
		// removes leading and trailing zeros
		void trim();
	public:
		// constructors
		RealNumber();
		RealNumber(const std::int64_t);
		RealNumber(const std::string&);
		RealNumber(const RealNumber&);
		
		// destructor
		~RealNumber();
		
		const RealNumber& operator=(const std::int64_t);
		const RealNumber& operator=(const std::string&);
		const RealNumber& operator=(const RealNumber&);
		
		// relational operators overload
		bool operator==(const RealNumber&) const ;
		bool operator!=(const RealNumber&) const ;
		bool operator<(const RealNumber&) const ;
		bool operator>(const RealNumber&) const ;
		bool operator<=(const RealNumber&) const ;
		bool operator>=(const RealNumber&) const ;
		
		// returns the opposite of the number
		RealNumber operator-() const ;
		
		// returns the absolute value of the number
		RealNumber absolute() const ;
		
		// returns the sum of the numbers
		RealNumber operator+(const RealNumber&) const ;
		
		// returns the subtraction of the numbers
		RealNumber operator-(const RealNumber&) const ;
		
		// returns the product of the numbers
		RealNumber operator*(const RealNumber&) const ;
};

#endif
