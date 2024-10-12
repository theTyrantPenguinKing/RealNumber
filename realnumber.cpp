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

bool RealNumber::operator==(const RealNumber& num) const {
	return this->sign == num.sign && compare(this->digits, num.digits) == 0;
}

bool RealNumber::operator!=(const RealNumber& num) const {
	return this->sign != num.sign || compare(this->digits, num.digits) != 0;
}

bool RealNumber::operator<(const RealNumber& num) const {
	std::int16_t cmp = compare(this->digits, num.digits);
	bool res;
	
	if(this->sign < num.sign){
		res = true;
	}else if(this->sign > num.sign){
		res = false;
	}else{
		if(this->sign > 0){
			if(cmp == 1){
				res = false;
			}else if(cmp == -1){
				res = true;
			}else{
				res = false;
			}
		}else if(this->sign < 0){
			if(cmp == 1){
				res = true;
			}else if(cmp == -1){
				res = false;
			}else{
				res = false;
			}
		}else{
			res = false;
		}
	}
	
	return res;
}

bool RealNumber::operator>(const RealNumber& num) const {
	std::int16_t cmp = compare(this->digits, num.digits);
	bool res;
	
	if(this->sign > num.sign){
		res = true;
	}else if(this->sign < num.sign){
		res = false;
	}else{
		if(this->sign > 0){
			if(cmp == 1){
				res = true;
			}else if(cmp == -1){
				res = false;
			}else{
				res = false;
			}
		}else if(this->sign < 0){
			if(cmp == 1){
				res = false;
			}else if(cmp == -1){
				res = true;
			}else{
				res = false;
			}
		}else{
			res = false;
		}
	}
	
	return res;
}

bool RealNumber::operator<=(const RealNumber& num) const {
	std::int16_t cmp = compare(this->digits, num.digits);
	bool res;
	
	if(this->sign < num.sign){
		res = true;
	}else if(this->sign > num.sign){
		res = false;
	}else{
		if(this->sign > 0){
			if(cmp == 1){
				res = false;
			}else if(cmp == -1){
				res = true;
			}else{
				res = true;
			}
		}else if(this->sign < 0){
			if(cmp == 1){
				res = true;
			}else if(cmp == -1){
				res = false;
			}else{
				res = true;
			}
		}else{
			res = true;
		}
	}
	
	return res;
}

bool RealNumber::operator>=(const RealNumber& num) const {
	std::int16_t cmp = compare(this->digits, num.digits);
	bool res;
	
	if(this->sign > num.sign){
		res = true;
	}else if(this->sign < num.sign){
		res = false;
	}else{
		if(this->sign > 0){
			if(cmp == 1){
				res = true;
			}else if(cmp == -1){
				res = false;
			}else{
				res = true;
			}
		}else if(this->sign < 0){
			if(cmp == 1){
				res = false;
			}else if(cmp == -1){
				res = true;
			}else{
				res = true;
			}
		}else{
			res = true;
		}
	}
	
	return res;
}

RealNumber RealNumber::operator-() const {
	RealNumber result = *this;
	result.sign *= -1;
	return result;
}

RealNumber RealNumber::absolute() const {
	RealNumber result = *this;
	
	if(result.sign == -1){
		result.sign = 1;
	}
	return result;
}

RealNumber RealNumber::operator+(const RealNumber& num) const {
	RealNumber res, a = *this, b = num;
	std::int16_t cmp = compare(this->digits, num.digits);
	
	while(a.precision < b.precision){
		a.digits.push_back(0);
		a.precision++;
	}
	while(b.precision < a.precision){
		b.digits.push_back(0);
		b.precision++;
	}
	
	if(this->sign == 0){
		res = num;
	}else if(num.sign == 0){
		res = *this;
	}else if(this->sign == num.sign){
		res.digits = addition(a.digits, b.digits);
		res.sign = this->sign;
		res.precision = a.precision;
	}else if(a.sign == 1 && num.sign == -1){
		res.digits = subtraction(a.digits, b.digits);
		if(cmp == 1){
			res.sign = 1;
		}else if(cmp == -1){
			res.sign = -1;
		}else{
			res.sign = 0;
		}
		res.precision = a.precision;
	}else if(this->sign == -1 && num.sign == 1){
		res.digits = subtraction(a.digits, b.digits);
		if(cmp == 1){
			res.sign = -1;
		}else if(cmp == -1){
			res.sign = 1;
		}else{
			res.sign = 0;
		}
		res.precision = a.precision;
	}
	
	res.trim();
	return res;
}

RealNumber RealNumber::operator-(const RealNumber& num) const {
	RealNumber res, a = *this, b = num;
	std::int16_t cmp = compare(this->digits, num.digits);
	
	while(a.precision < b.precision){
		a.digits.push_back(0);
		a.precision++;
	}
	while(b.precision < a.precision){
		b.digits.push_back(0);
		b.precision++;
	}
	
	if(this->sign == 0){
		res = -num;
	}else if(num.sign == 0){
		res = *this;
	}else if(this->sign == 1 && num.sign == 1){
		res.digits = subtraction(a.digits, b.digits);
		if(cmp == 1){
			res.sign = 1;
		}else if(cmp == -1){
			res.sign = -1;
		}else{
			res.sign = 0;
		}
		res.precision = a.precision;
	}else if(this->sign == 1 && num.sign == -1){
		res.digits = addition(a.digits, b.digits);
		res.sign = 1;
		res.precision = a.precision;
	}else if(this->sign == -1 && num.sign == 1){
		res.digits = addition(a.digits, b.digits);
		res.sign = -1;
		res.precision = a.precision;
	}else{
		res.digits = subtraction(a.digits, b.digits);
		if(cmp == 1){
			res.sign = -1;
		}else if(cmp == -1){
			res.sign = 1;
		}else{
			res.sign = 0;
		}
	}
	
	res.trim();
	return res;
}

RealNumber RealNumber::operator*(const RealNumber& num) const {
	RealNumber res, a = *this, b = num;
	
	while(a.precision < b.precision){
		a.digits.push_back(0);
		a.precision++;
	}
	while(b.precision < a.precision){
		b.digits.push_back(0);
		b.precision++;
	}
	
	if(a.digits.size() <= 64 || b.digits.size() <= 64){
		res.digits = multiply(a.digits, b.digits);
	}else{
		res.digits = karatsuba(a.digits, b.digits);
	}
	
	res.sign = a.sign * b.sign;
	res.precision = a.precision + b.precision;
	
	res.trim();
	return res;
}

const RealNumber& RealNumber::operator+=(const RealNumber& num){
	return *this = *this + num;
}

const RealNumber& RealNumber::operator+=(const std::int64_t num){
	return *this = *this + num;
}

const RealNumber& RealNumber::operator+=(const std::string& num){
	return *this = *this + num;
}

const RealNumber& RealNumber::operator-=(const RealNumber& num){
	return *this = *this - num;
}

const RealNumber& RealNumber::operator-=(const std::int64_t num){
	return *this = *this - num;
}

const RealNumber& RealNumber::operator-=(const std::string& num){
	return *this = *this - num;
}

const RealNumber& RealNumber::operator*=(const RealNumber& num){
	return *this = *this * num;
}

const RealNumber& RealNumber::operator*=(const std::int64_t num){
	return *this = *this * num;
}

const RealNumber& RealNumber::operator*=(const std::string& num){
	return *this = *this * num;
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

/******************************************************************************
FRIEND METHODS
******************************************************************************/

std::ostream& operator<<(std::ostream& out, const RealNumber& num){
	if(num.sign == -1){
		out << "-";
	}
	
	std::deque<std::int16_t>::const_iterator it, afterPoint;
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

bool operator==(const std::int64_t num1, const RealNumber& num2){
	return RealNumber(num1) == num2;
}

bool operator==(const std::string& num1, const RealNumber& num2){
	return RealNumber(num1) == num2;
}

bool operator!=(const std::int64_t num1, const RealNumber& num2){
	return RealNumber(num1) != num2;
}

bool operator!=(const std::string& num1, const RealNumber& num2){
	return RealNumber(num1) != num2;
}

bool operator<(const std::int64_t num1, const RealNumber& num2){
	return RealNumber(num1) < num2;
}

bool operator<(const std::string& num1, const RealNumber& num2){
	return RealNumber(num1) < num2;
}

bool operator>(const std::int64_t num1, const RealNumber& num2){
	return RealNumber(num1) > num2;
}

bool operator>(const std::string& num1, const RealNumber& num2){
	return RealNumber(num1) > num2;
}

bool operator<=(const std::int64_t num1, const RealNumber& num2){
	return RealNumber(num1) <= num2;
}

bool operator<=(const std::string& num1, const RealNumber& num2){
	return RealNumber(num1) <= num2;
}

bool operator>=(const std::int64_t num1, const RealNumber& num2){
	return RealNumber(num1) >= num2;
}

bool operator>=(const std::string& num1, const RealNumber& num2){
	return RealNumber(num1) >= num2;
}

RealNumber operator+(const std::int64_t num1, const RealNumber& num2){
	return RealNumber(num1) + num2;
}

RealNumber operator+(const std::string& num1, const RealNumber& num2){
	return RealNumber(num1) + num2;
}

RealNumber operator-(const std::int64_t num1, const RealNumber& num2){
	return RealNumber(num1) - num2;
}

RealNumber operator-(const std::string& num1, const RealNumber& num2){
	return RealNumber(num1) - num2;
}

RealNumber operator*(const std::int64_t num1, const RealNumber& num2){
	return RealNumber(num1) * num2;
}

RealNumber operator*(const std::string& num1, const RealNumber& num2){
	return RealNumber(num1) * num2;
}
