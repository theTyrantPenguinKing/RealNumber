#include "realnumber.hpp"

/******************************************************************************
MÉTODOS PÚBLICOS
******************************************************************************/

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
		for(; it != str.end() && isdigit(*it); it++){
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
	
	for(it = this->digits.begin(); it != this->digits.end(); it++){
		if(it == afterPoint){
			str.push_back('.');
		}
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
	for(; it != r.digits.end(); it++){
		if(it == afterPoint){
			out << ".";
		}
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
