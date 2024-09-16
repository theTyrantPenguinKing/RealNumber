#include "realnumber.hpp"

/******************************************************************************
MÉTODOS PÚBLICOS
******************************************************************************/

std::size_t RealNumber::maxScale = DEFAULT_MAX_SCALE;

RealNumber::RealNumber(){
	this->digits.push_back(0);
	this->sign = 0;
	this->scale = 0;
}

RealNumber::RealNumber(const std::int64_t num){
	*this = num;
}

RealNumber::RealNumber(const std::string& str){
	*this = str;
}

RealNumber::RealNumber(const RealNumber& r){
	this->digits = r.digits;
	this->sign = r.sign;
	this->scale = r.scale;
}

RealNumber::~RealNumber(){
	this->digits.clear();
}

const RealNumber& RealNumber::operator=(const RealNumber& r){
	if(this != &r){	// evita auto-asignación
		this->digits = r.digits;
		this->sign = r.sign;
		this->scale = r.scale;
	}
	return *this;
}

const RealNumber& RealNumber::operator=(const std::int64_t num){
	std::int64_t aux = std::abs(num);
	
	this->digits.clear();
	this->scale = 0;
	
	if(num < 0){
		this->sign = -1;
	}else if(num > 0){
		this->sign = 1;
	}else{
		this->sign = 0;
	}
	
	do{
		this->digits.push_front(aux % 10);
		aux /= 10;
	}while(aux != 0);
	
	return *this;
}

const RealNumber& RealNumber::operator=(const std::string& str){
	std::string::const_iterator it;
	
	this->digits.clear();
	// el número nuevo es positivo hasta que se demuestre lo contrario
	this->sign = 1;
	this->scale = 0;
	
	it = str.begin();
	
	// ignoramos los espacios en blanco
	for(; it != str.end() && isblank(*it); it++);
	
	if(it != str.end() && *it == '+'){
		it++;
	}else if(it != str.end() && *it == '-'){
		this->sign = -1;
		it++;
	}
	
	// ignoramos los ceros al comienzo del número real
	for(; it != str.end() && *it == '0'; it++);
	
	for(; it != str.end() && isdigit(*it); it++){
		this->digits.push_back(*it - '0');
	}
	
	if(it != str.end() && *it == '.'){
		if(this->digits.empty()){
			// insertamos un cero antes del punto decimal
			this->digits.push_back(0);
		}
		it++;
		for(; it != str.end() && isdigit(*it) && this->scale < RealNumber::maxScale; it++){
			this->digits.push_back(*it - '0');
			this->scale++;
		}
	}
	
	if(this->digits.empty()){
		this->digits.push_back(0);
		this->sign = 0;
		this->scale = 0;
	}
	
	this->trimRealNumber();
	
	return *this;
}

std::string RealNumber::toString() const {
	std::string str;
	std::deque<std::uint16_t>::const_iterator it;
	std::deque<std::uint16_t>::const_iterator afterPoint = this->digits.begin();
	std::advance(afterPoint, this->getPrecision() - this->getScale());
	
	if(this->sign < 0){
		str = "-";
	}
	
	for(it = this->digits.begin(); it != afterPoint; it++){
		str.push_back(*it + '0');
	}
	
	if(it != this->digits.end()){
		str.push_back('.');
	}
	
	for(; it != this->digits.end(); it++){
		str.push_back(*it + '0');
	}
	
	return str;
}

std::size_t RealNumber::getPrecision() const {
	return this->digits.size();
}

std::size_t RealNumber::getScale() const {
	return this->scale;
}

void RealNumber::setMaxScale(const std::size_t mScale){
	RealNumber::maxScale = mScale;
}

bool RealNumber::operator==(const RealNumber& r) const {
	return !compare(*this, r);
}

bool RealNumber::operator!=(const RealNumber& r) const {
	return compare(*this, r) != 0;
}

bool RealNumber::operator<(const RealNumber& r) const {
	return compare(*this, r) < 0;
}

bool RealNumber::operator<=(const RealNumber& r) const {
	return compare(*this, r) <= 0;
}

bool RealNumber::operator>(const RealNumber& r) const {
	return compare(*this, r) > 0;
}

bool RealNumber::operator>=(const RealNumber& r) const {
	return compare(*this, r) >= 0;
}

RealNumber RealNumber::absolute() const {
	RealNumber a(*this);
	
	if(a.sign < 0){
		a.sign = 1;
	}
	return a;
}

RealNumber RealNumber::operator-() const {
	RealNumber op(*this);
	op.sign *= -1;
	return op;
}

/******************************************************************************
MÉTODOS PRIVADOS
******************************************************************************/

void RealNumber::trimRealNumber(){
	// eliminamos los ceros al comienzo del número hasta que solo quede un
	// dígito antes del punto decimal
	while(this->digits.size() > this->scale + 1 && this->digits.front() == 0){
		this->digits.pop_front();
	}
	
	// elimina los ceros al final del número hasta que no queden ceros
	// después del punto decimal
	while(this->scale && this->digits.back() == 0){
		this->digits.pop_back();
		this->scale--;
	}
	
	// cambiamos el signo a cero
	if(this->digits.size() == 1 && this->digits.front() == 0){
		this->sign = 0;
	}
}

void RealNumber::addLeadingZeros(std::size_t num_zeros){
	for(size_t i = 0; i < num_zeros; i++){
		this->digits.push_front(0);
	}
}

void RealNumber::addEndingZeros(std::size_t num_zeros){
	for(size_t i = 0; i < num_zeros; i++){
		this->digits.push_back(0);
		this->scale++;
	}
}

/******************************************************************************
MÉTODOS AMIGO
******************************************************************************/

std::ostream& operator<<(std::ostream& out, const RealNumber& r){
	std::deque<std::uint16_t>::const_iterator it = r.digits.begin();
	std::deque<std::uint16_t>::const_iterator afterPoint = r.digits.begin();
	std::advance(afterPoint, r.getPrecision() - r.getScale());
	
	if(r.sign < 0){
		out << "-";
	}
	
	for(; it != afterPoint; it++){
		out << *it;
	}
	if(it != r.digits.end()){
		out << ".";
	}
	for(; it != r.digits.end(); it++){
		out << *it;
	}
	
	return out;
}

std::istream& operator>>(std::istream& in, RealNumber& r){
	std::string str;
	
	std::getline(in, str);
	
	r = str;
	
	return in;
}

int16_t compare(const RealNumber& r1, const RealNumber& r2){
	int16_t cmp = 0;
	
	const std::size_t s1 = r1.digits.size() - r1.scale;
	const std::size_t s2 = r2.digits.size() - r2.scale;
	
	std::deque<uint16_t>::const_iterator it1 = r1.digits.begin();
	std::deque<uint16_t>::const_iterator it2 = r2.digits.begin();
	
	if(r1.sign < r2.sign){
		cmp = -1;
	}else if(r1.sign > r2.sign){
		cmp = 1;
	}else{
		// ambos números tienen el mismo signo
		
		if(r1.sign > 0){
			if(s1 > s2){
				cmp = 1;
			}else if(s1 < s2){
				cmp = -1;
			}else{
				for(; !cmp && it1 != r1.digits.end() && it2 != r2.digits.end(); it1++, it2++){
					if(*it1 < *it2){
						cmp = -1;
					}else if(*it1 > *it2){
						cmp = 1;
					}
				}
				
				if(!cmp){
					if(it1 != r1.digits.end()){
						cmp = 1;
					}else if(it2 != r2.digits.end()){
						cmp = -1;
					}else{
						cmp = 0;
					}
				}
			}
		}else if(r1.sign < 0){
			if(s1 > s2){
				cmp = -1;
			}else if(s1 < s2){
				cmp = 1;
			}else{
				for(; !cmp && it1 != r1.digits.end() && it2 != r2.digits.end(); it1++, it2++){
					if(*it1 < *it2){
						cmp = 1;
					}else if(*it1 > *it2){
						cmp = -1;
					}
				}
				
				if(!cmp){
					if(it1 != r1.digits.end()){
						cmp = -1;
					}else if(it2 != r2.digits.end()){
						cmp = 1;
					}else{
						cmp = 0;
					}
				}
			}
		}else{
			cmp = 0;
		}
	}
	
	return cmp;
}

bool operator==(const std::int64_t num, const RealNumber& r){
	return !compare(RealNumber(num), r);
}

bool operator==(const std::string& num, const RealNumber& r){
	return !compare(RealNumber(num), r);
}

bool operator!=(const std::int64_t num, const RealNumber& r){
	return compare(RealNumber(num), r) != 0;
}

bool operator!=(const std::string& num, const RealNumber& r){
	return compare(RealNumber(num), r) != 0;
}

bool operator<(const std::int64_t num, const RealNumber& r){
	return compare(RealNumber(num), r) < 0;
}

bool operator<(const std::string num, const RealNumber& r){
	return compare(RealNumber(num), r) < 0;
}

bool operator<=(const std::int64_t num, const RealNumber& r){
	return compare(RealNumber(num), r) <= 0;
}

bool operator<=(const std::string& num, const RealNumber& r){
	return compare(RealNumber(num), r) <= 0;
}

bool operator>(const std::int64_t num, const RealNumber& r){
	return compare(RealNumber(num), r) > 0;
}

bool operator>(const std::string& num, const RealNumber& r){
	return compare(RealNumber(num), r) > 0;
}

bool operator>=(const std::int64_t num, const RealNumber& r){
	return compare(RealNumber(num), r) >= 0;
}

bool operator>=(const std::string& num, const RealNumber& r){
	return compare(RealNumber(num), r) >= 0;
}
