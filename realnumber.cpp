#include "realnumber.hpp"

std::size_t RealNumber::max_scale = DEFAULT_SCALE;

/******************************************************************************
PUBLIC METHODS
******************************************************************************/

RealNumber::RealNumber(const std::string& str){
	*this = str;
}

RealNumber::RealNumber(const RealNumber& num){
	this->integer_digits = num.integer_digits;
	this->scale_digits = num.scale_digits;
	this->sign = num.sign;
}

RealNumber::RealNumber(const char * str){
	*this = std::string(str);
}

RealNumber::~RealNumber(){
	this->integer_digits.clear();
	this->scale_digits.clear();
	this->sign = 0;
}

const RealNumber& RealNumber::operator=(const RealNumber& num){
	if(this != &num){
		this->integer_digits = num.integer_digits;
		this->scale_digits = num.scale_digits;
		this->sign = num.sign;
	}
	return *this;
}

const RealNumber& RealNumber::operator=(const std::string& str){
	auto iter = str.begin();
	
	this->integer_digits.clear();
	this->scale_digits.clear();
	this->sign = 1;
	
	// skip blank spaces
	for(; iter != str.end() && isblank(*iter); iter++);
	
	if(iter != str.end()){
		if(*iter == '+'){
			iter++;
		}else if(*iter == '-'){
			this->sign = -1;
			iter++;
		}
	}
	
	// skip leading zeros
	for(; iter != str.end() && *iter == '0'; iter++);
	
	for(; iter != str.end() && isdigit(*iter); iter++){
		this->integer_digits.push_back(*iter - '0');
	}
	
	if(iter != str.end() && *iter == '.'){
		if(this->integer_digits.empty()){
			this->integer_digits.push_back(0);
		}
		iter++;
		for(; iter != str.end() && isdigit(*iter); iter++){
			this->scale_digits.push_back(*iter - '0');
		}
	}
	
	this->removeZeros();
	
	return *this;
}

bool RealNumber::operator==(const RealNumber& num) const {
	return RealNumber::compare(*this, num) == 0;
}

bool RealNumber::operator!=(const RealNumber& num) const {
	return RealNumber::compare(*this, num) != 0;
}

bool RealNumber::operator<(const RealNumber& num) const {
	return RealNumber::compare(*this, num) < 0;
}

bool RealNumber::operator>(const RealNumber& num) const {
	return RealNumber::compare(*this, num) > 0;
}

bool RealNumber::operator<=(const RealNumber& num) const {
	return RealNumber::compare(*this, num) <= 0;
}

bool RealNumber::operator>=(const RealNumber& num) const {
	return RealNumber::compare(*this, num) >= 0;
}

std::string RealNumber::toString() const {
	auto iter = this->integer_digits.begin();
	std::string res;
	
	if(this->sign < 0){
		res = "-";
	}
	
	for(; iter != this->integer_digits.end(); iter++){
		res += *iter + '0';
	}
	
	if(!this->scale_digits.empty()){
		iter = this->scale_digits.begin();
		res += '.';
		for(; iter != this->scale_digits.end(); iter++){
			res += *iter + '0';
		}
	}
	
	return res;
}

/******************************************************************************
PRIVATE METHODS
******************************************************************************/

void RealNumber::removeZeros(){
	while(!this->integer_digits.empty() && this->integer_digits.front() == 0){
		this->integer_digits.pop_front();
	}
	
	while(!this->scale_digits.empty() && this->scale_digits.back() == 0){
		this->scale_digits.pop_back();
	}
	
	if(this->integer_digits.empty() && this->scale_digits.empty()){
		this->sign = 0;
	}
	
	if(this->integer_digits.empty()){
		this->integer_digits.push_back(0);
	}
}

/******************************************************************************
FRIEND METHODS
******************************************************************************/

std::ostream& operator<<(std::ostream& stream, const RealNumber& num){
	stream << num.toString();
	return stream;
}

std::istream& operator>>(std::istream& stream, RealNumber& num){
	std::string input_string;
	std::getline(stream, input_string);
	num = input_string;
	return stream;
}

bool operator==(const std::string& num1, const RealNumber& num2){
	return RealNumber(num1) == num2;
}

bool operator!=(const std::string& num1, const RealNumber& num2){
	return RealNumber(num1) != num2;
}

/******************************************************************************
STATIC METHODS
******************************************************************************/

void RealNumber::setMaxScale(const std::size_t scale){
	RealNumber::max_scale = scale;
}

std::int16_t RealNumber::compare(const RealNumber& num1,
const RealNumber& num2){
	std::int16_t cmp;
	bool stop = false;
	const std::size_t s_num1 = num1.integer_digits.size();
	const std::size_t s_num2 = num2.integer_digits.size();
	
	if(num1.sign < num2.sign){
		cmp = -1;
	}else if(num1.sign > num2.sign){
		cmp = 1;
	}else{
		if(s_num1 > s_num2){
			if(num1.sign > 0){
				cmp = 1;
			}else{
				cmp = -1;
			}
		}else if(s_num1 < s_num2){
			if(num1.sign > 0){
				cmp = -1;
			}else{
				cmp = 1;
			}
		}else{
			auto iter1 = num1.integer_digits.begin();
			auto iter2 = num2.integer_digits.begin();
			
			for(; !stop && iter1 != num1.integer_digits.end() &&
			iter2 != num2.integer_digits.end(); iter1++, iter2++){
				if(*iter1 > *iter2){
					if(num1.sign > 0){
						cmp = 1;
					}else{
						cmp = -1;
					}
					stop = true;
				}else if(*iter1 < *iter2){
					if(num1.sign > 0){
						cmp = -1;
					}else{
						cmp = 1;
					}
					stop = true;
				}
			}
			
			if(!stop){
				iter1 = num1.scale_digits.begin();
				iter2 = num2.scale_digits.begin();
				
				for(; !stop && iter1 != num1.scale_digits.end() &&
				iter2 != num2.scale_digits.end(); iter1++, iter2++){
					if(*iter1 > *iter2){
						if(num1.sign > 0){
							cmp = 1;
						}else{
							cmp = -1;
						}
						stop = true;
					}else if(*iter1 < *iter2){
						if(num1.sign > 0){
							cmp = -1;
						}else{
							cmp = 1;
						}
						stop = true;
					}
				}
				
				if(!stop){
					if(iter1 != num1.scale_digits.end() &&
					iter2 == num2.scale_digits.end()){
						if(num1.sign > 0){
							cmp = 1;
						}else{
							cmp = -1;
						}
					}else if(iter1 == num1.scale_digits.end() &&
						iter2 != num2.scale_digits.end()){
						if(num1.sign > 0){
							cmp = -1;
						}else{
							cmp = 1;
						}
					}else{
						cmp = 0;
					}
				}
			}
		}
	}
	
	return cmp;
}
