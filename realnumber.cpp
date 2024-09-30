#include "realnumber.hpp"

RealNumber::RealNumber(){
	this->digits.push_back(0);
	this->sign = 0;
	this->precision = 0;
}

RealNumber::RealNumber(const std::int64_t num){
	*this = num;
}

RealNumber::RealNumber(const std::string& num){
	*this = num;
}

RealNumber::RealNumber(const RealNumber& num){
	this->digits = num.digits;
	this->sign = num.sign;
	this->precision = num.precision;
}

RealNumber::~RealNumber(){
	this->digits.clear();
	this->sign = 0;
	this->precision = 0;
}

const RealNumber& RealNumber::operator=(const std::int64_t num){
	this->digits.clear();
	this->precision = 0;
	std::int64_t aux = std::abs(num);
	
	if(num > 0){
		this->sign = 1;
	}else if(num < 0){
		this->sign = -1;
	}else{
		this->sign = 0;
	}
	
	do{
		this->digits.push_front(aux % 10);
		aux /= 10;
	}while(aux != 0);
	
	return *this;
}

const RealNumber& RealNumber::operator=(const std::string& num){
	this->digits.clear();
	this->sign = 0;
	this->precision = 0;
	
	if(num.empty()){
		this->digits.push_back(0);
	}else{
		// the number is positive for now
		this->sign = 1;
		
		std::string::const_iterator it = num.begin();
		
		// skip initial blank spaces
		for(; it != num.end() && isblank(*it); it++);
		
		if(it != num.end()){
			if(*it == '+'){
				it++;
			}else if(*it == '-'){
				this->sign = -1;
				it++;
			}
			
			// skip initial zeros
			for(; it != num.end() && *it == '0'; it++);
			
			for(; it != num.end() && isdigit(*it); it++){
				this->digits.push_back(*it - '0');
			}
			
			if(it != num.end() && *it == '.'){
				if(this->digits.empty()){
					this->digits.push_front(0);
				}
				it++;
				for(; it != num.end(); it++){
					this->digits.push_back(*it - '0');
					this->precision++;
				}
			}
		}
	}
	
	this->trim();
	
	return *this;
}

const RealNumber& RealNumber::operator=(const RealNumber& num){
	if(this != &num){
		this->digits = num.digits;
		this->sign = num.sign;
		this->precision = num.precision;
	}
	
	return *this;
}

std::size_t RealNumber::getMantissa() const {
	return this->digits.size() - this->precision;
}

std::size_t RealNumber::getPrecision() const {
	return this->precision;
}

bool RealNumber::operator==(const RealNumber& num) const {
	return this->sign == num.sign && RealNumber::compare(*this, num) == 0;
}

bool RealNumber::operator!=(const RealNumber& num) const {
	return this->sign != num.sign || RealNumber::compare(*this, num) != 0;
}

bool RealNumber::operator<(const RealNumber& num) const {
	bool lt;
	std::int16_t cmp;
	
	if(this->sign < num.sign){
		lt = true;
	}else if(this->sign > num.sign){
		lt = false;
	}else{
		cmp = RealNumber::compare(*this, num);
		if(this->sign > 0){
			if(cmp < 0){
				lt = true;
			}else{
				lt = false;
			}
		}else if(this->sign < 0){
			if(cmp > 0){
				lt = true;
			}else{
				lt = false;
			}
		}else{
			lt = false;
		}
	}
	
	return lt;
}

bool RealNumber::operator<=(const RealNumber& num) const {
	bool lteq;
	std::int16_t cmp;
	
	if(this->sign < num.sign){
		lteq = true;
	}else if(this->sign > num.sign){
		lteq = false;
	}else{
		cmp =  RealNumber::compare(*this, num);
		
		if(this->sign > 0){
			if(cmp <= 0){
				lteq = true;
			}else{
				lteq = false;
			}
		}else if(this->sign < 0){
			if(cmp >= 0){
				lteq = true;
			}else{
				lteq = false;
			}
		}else{
			lteq = true;
		}
	}
	
	return lteq;
}

bool RealNumber::operator>(const RealNumber& num) const {
	bool gt;
	std::int16_t cmp;
	
	if(this->sign > num.sign){
		gt = true;
	}else if(this->sign < num.sign){
		gt = false;
	}else{
		cmp = RealNumber::compare(*this, num);
		
		if(this->sign > 0){
			if(cmp > 0){
				gt = true;
			}else{
				gt = false;
			}
		}else if(this->sign < 0){
			if(cmp < 0){
				gt = true;
			}else{
				gt = false;
			}
		}else{
			gt = false;
		}
	}
	
	return gt;
}

bool RealNumber::operator>=(const RealNumber& num) const {
	bool gteq;
	std::int16_t cmp;
	
	if(this->sign > num.sign){
		gteq = true;
	}else if(this->sign < num.sign){
		gteq = false;
	}else{
		cmp = RealNumber::compare(*this, num);
		
		if(this->sign > 0){
			if(cmp >= 0){
				gteq = true;
			}else{
				gteq = false;
			}
		}else if(this->sign < 0){
			if(cmp <= 0){
				gteq = true;
			}else{
				gteq = false;
			}
		}else{
			gteq = true;
		}
	}
	
	return gteq;
}

/******************************************************************************
PRIVATE METHODS
******************************************************************************/

void RealNumber::trim(){
	if(this->digits.empty()){
		this->digits.push_back(0);
 		this->precision = 0;
 		this->sign = 0;
 	}
 	
 	while(this->digits.size() > this->precision + 1 &&
 	this->digits.front() == 0){
 		this->digits.pop_front();
 	}
 	
 	while(this->precision && this->digits.back() == 0){
 		this->digits.pop_back();
 		this->precision--;
 	}
 	
 	if(this->digits.size() == 1 && this->digits.front() == 0){
 		this->sign = 0;
 	}
}

std::int16_t RealNumber::compare(const RealNumber& n1, const RealNumber& n2){
	std::int16_t cmp = 0;
	const std::size_t s1 = n1.digits.size() - n1.precision;
	const std::size_t s2 = n2.digits.size() - n2.precision;
	bool exit = false;
	
	if(s1 > s2){
		cmp = 1;
	}else if(s1 < s2){
		cmp = -1;
	}else{
		std::deque<std::uint16_t>::const_iterator it1, it2;
		
		it1 = n1.digits.begin();
		it2 = n2.digits.begin();
		
		for(; !exit && it1 != n1.digits.end() && it2 != n2.digits.end()
		; it1++, it2++){
			if(*it1 > *it2){
				cmp = 1;
				exit = true;
			}else if(*it1 < *it2){
				cmp = -1;
				exit = true;
			}
		}
		
		if(!exit){
			if(it1 != n1.digits.end()){
				cmp = 1;
			}else if(it2 != n2.digits.end()){
				cmp = -1;
			}else{
				cmp = 0;
			}
		}
	}
	
	return cmp;
}

/******************************************************************************
FRIEND METHODS
******************************************************************************/

std::ostream& operator<<(std::ostream& out, const RealNumber& num){
	if(num.sign == -1){
		out << "-";
	}
	
	std::deque<std::uint16_t>::const_iterator it, afterPoint;
	afterPoint = num.digits.begin();
	std::advance(afterPoint, num.digits.size() - num.precision);
	
	for(it = num.digits.begin(); it != afterPoint; it++){
		out << *it;
	}
	
	if(it != num.digits.end()){
		out << ".";
		for(; it != num.digits.end(); it++){
			out << *it;
		}
	}
	
	return out;
}

std::istream& operator>>(std::istream& in, RealNumber& num){
	std::string s;
	std::getline(in, s);
	
	num = s;
	
	return in;
}

bool operator==(const std::int64_t n1, const RealNumber& n2){
	return RealNumber(n1) == n2;
}

bool operator==(const std::string& n1, const RealNumber& n2){
	return RealNumber(n1) == n2;
}

bool operator!=(const std::int64_t n1, const RealNumber& n2){
	return RealNumber(n1) != n2;
}

bool operator!=(const std::string& n1, const RealNumber& n2){
	return RealNumber(n1) != n2;
}

bool operator<(const std::int64_t n1, const RealNumber& n2){
	return RealNumber(n1) < n2;
}

bool operator<(const std::string& n1, const RealNumber& n2){
	return RealNumber(n1) < n2;
}

bool operator<=(const std::int64_t n1, const RealNumber& n2){
	return RealNumber(n1) <= n2;
}

bool operator<=(const std::string& n1, const RealNumber& n2){
	return RealNumber(n1) <= n2;
}

bool operator>(const std::int64_t n1, const RealNumber& n2){
	return RealNumber(n1) > n2;
}

bool operator>(const std::string& n1, const RealNumber& n2){
	return RealNumber(n1) > n2;
}

bool operator>=(const std::int64_t n1, const RealNumber& n2){
	return RealNumber(n1) < n2;
}

bool operator>=(const std::string& n1, const RealNumber& n2){
	return RealNumber(n1) < n2;
}
