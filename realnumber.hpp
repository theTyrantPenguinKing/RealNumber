#ifndef REALNUMBER_HPP
#define REALNUMBER_HPP

#include <iostream>
#include <deque>
#include <cinttypes>
#include <string>
#include <cctype>

const std::size_t DEFAULT_SCALE = 9;

class RealNumber{
	// stream insertion overload
	friend std::ostream& operator<<(std::ostream&, const RealNumber&);
	
	// stream extraction overload
	friend std::istream& operator>>(std::istream&, RealNumber&);
	
	// equality overloads
	friend bool operator==(const std::string&, const RealNumber&);
	friend bool operator==(const char*, const RealNumber&);
	
	// inequality overloads
	friend bool operator!=(const std::string&, const RealNumber&);
	friend bool operator!=(const char*, const RealNumber&);
	
	// less than overloads
	friend bool operator<(const std::string&, const RealNumber&);
	friend bool operator<(const char*, const RealNumber&);
	
	// greater than overloads
	friend bool operator>(const std::string&, const RealNumber&);
	friend bool operator>(const char*, const RealNumber&);
	
	// less than or equal to overloads
	friend bool operator<=(const std::string&, const RealNumber&);
	friend bool operator<=(const char*, const RealNumber&);
	
	// greater than or equal to overloads
	friend bool operator>=(const std::string&, const RealNumber&);
	friend bool operator>=(const char*, const RealNumber&);
	
	private:
		// digits before decimal point
		std::deque<std::int16_t> integer_digits{0};
		
		// digits after decimal point
		std::deque<std::int16_t> scale_digits{};
		
		// sign of the number
		int16_t sign{0};
		
		// maximum amount of digits after the decimal point
		static std::size_t max_scale;
		
		// removes leading and trailing zeros
		void removeZeros();
		
		/*
		Compares two real numbers and returns:
			1 if the first number is greater than the second
			0 if they're equals
			-1 if the first is less than the second
		*/
		static std::int16_t compare(const RealNumber&, const RealNumber&);
		
	public:
		// constructors
		RealNumber() = default;
		RealNumber(const std::string&);
		RealNumber(const char *);
		RealNumber(const RealNumber&);
		
		// destructor
		~RealNumber();
		
		// assignment overloads
		const RealNumber& operator=(const RealNumber&);
		const RealNumber& operator=(const std::string&);
		
		// equality overload
		bool operator==(const RealNumber&) const ;
		
		// inequality overload
		bool operator!=(const RealNumber&) const ;
		
		// less than overload
		bool operator<(const RealNumber&) const ;
		
		// greater than overload
		bool operator>(const RealNumber&) const ;
		
		// less than or equal to overload
		bool operator<=(const RealNumber&) const ;
		
		// greater than or equal to overload
		bool operator>=(const RealNumber&) const ;
		
		// converts the real number to a string
		std::string toString() const ;
		
		// gets the precision of the real number
		std::size_t getPrecision() const ;
		
		// gets the scale of the real number
		std::size_t getScale() const ;
		
		// sets the maximum scale
		static void setMaxScale(const std::size_t);
};

#endif
