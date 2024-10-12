#include "rn_utils.hpp"

#include <iostream>

std::int16_t compare(const std::deque<std::int16_t>& num1,
const std::deque<std::int16_t>& num2){
	
	bool exit = false;
	std::deque<std::int16_t>::const_iterator it1, it2;
	std::int16_t cmp;
	
	if(num1.size() > num2.size()){
		cmp = 1;
	}else if(num1.size() < num2.size()){
		cmp = -1;
	}else{
		for(it1 = num1.begin(), it2 = num2.begin(); !exit && it1 != num1.end() &&
		it2 != num2.end(); it1++, it2++){
			if(*it1 > *it2){
				cmp = 1;
				exit = true;
			}else if(*it1 < *it2){
				cmp = -1;
				exit = true;
			}
		}
	
		if(!exit){
			if(it1 != num1.end() && it2 == num2.end()){
				cmp = 1;
			}else if(it1 == num1.end() && it2 != num2.end()){
				cmp = -1;
			}else{
				cmp = 0;
			}
		}
	}
	
	return cmp;
}

void split(const std::deque<std::int16_t>& num, std::deque<std::int16_t>& left,
std::deque<std::int16_t>& right){
	left.clear();
	right.clear();
	
	std::deque<std::int16_t>::const_iterator it, halfIter;
	it = num.begin();
	halfIter = num.begin();
	std::advance(halfIter, num.size() / 2);
	
	for(; it != halfIter; it++){
		left.push_back(*it);
	}
	for(; it != num.end(); it++){
		right.push_back(*it);
	}
}

std::deque<std::int16_t> addition(const std::deque<std::int16_t>& num1,
const std::deque<std::int16_t>& num2){
	std::deque<std::int16_t> result;
	std::deque<std::int16_t>::const_reverse_iterator it1, it2;
	std::int16_t val, carry = 0;
	
	for(it1 = num1.rbegin(), it2 = num2.rbegin(); it1 != num1.rend() &&
	it2 != num2.rend(); it1++, it2++){
		val = *it1 + *it2 + carry;
		if(val > 9){
			carry = 1;
			val -= 10;
		}else{
			carry = 0;
		}
		
		result.push_front(val);
	}
	
	for(; it1 != num1.rend(); it1++){
		val = *it1 + carry;
		if(val > 9){
			carry = 1;
			val -= 10;
		}else{
			carry = 0;
		}
		
		result.push_front(val);
	}
	
	for(; it2 != num2.rend(); it2++){
		val = *it2 + carry;
		if(val > 9){
			carry = 1;
			val -= 10;
		}else{
			carry = 0;
		}
		
		result.push_front(val);
	}
	
	if(carry){
		result.push_front(carry);
	}
	
	return result;
}

std::deque<std::int16_t> subtraction(const std::deque<std::int16_t>& num1,
const std::deque<std::int16_t>& num2){
	std::deque<std::int16_t> result, n1 = num1, n2 = num2;
	std::deque<std::int16_t>::const_reverse_iterator it1, it2;
	std::int16_t val, carry = 0, a, b;
	
	if(compare(n1, n2) == -1){
		// if the first number is less than the second then swap them
		std::swap(n1, n2);
	}
	
	for(it1 = n1.rbegin(), it2 = n2.rbegin(); it1 != n1.rend() &&
	it2 != n2.rend(); it1++, it2++){
		a = *it1;
		b = *it2;
		if(carry){
			a -= 1;
		}
		
		if(a < b){
			val = a + 10 -b;
			carry = 1;
		}else{
			val = a - b;
			carry = 0;
		}
		result.push_front(val);
	}
	
	for(; it1 != n1.rend(); it1++){
		a = *it1;
		if(carry){
			a -= 1;
		}
		
		if(a < 0){
			val = a + 10;
			carry = 1;
		}else{
			val = a;
			carry = 0;
		}
		result.push_front(val);
	}
	
	return result;
}

std::deque<std::int16_t> multiply10(const std::deque<std::int16_t>& num,
const std::size_t amount){
	std::deque<std::int16_t> result = num;
	
	for(std::size_t i = 0; i < amount; i++){
		result.push_back(0);
	}
	return result;
}

std::deque<std::int16_t> multiply(const std::deque<std::int16_t>& num1,
const std::deque<std::int16_t>& num2){
	std::deque<std::int16_t> result, aux;
	std::deque<std::int16_t>::const_reverse_iterator it1, it2;
	std::int16_t val, carry = 0;
	std::size_t shift = 0;
	
	result.push_front(0);
	
	if(num1.empty() || num2.empty()){
		return result;
	}
	
	for(it2 = num2.rbegin(); it2 != num2.rend(); it2++, shift++){
		if(*it2 != 0){
			for(std::size_t s = 0; s < shift; s++){
				aux.push_front(0);
			}
			for(it1 = num1.rbegin(); it1 != num1.rend(); it1++){
				val = *it1 * *it2 + carry;
				if(val > 9){
					carry = val / 10;
					val %= 10;
				}else{
					carry = 0;
				}
				aux.push_front(val);
			}
			
			if(carry){
				aux.push_front(carry);
				carry = 0;
			}
			
			result = addition(aux, result);
			
			aux.clear();
		}
	}
	
	return result;
}

std::deque<std::int16_t> karatsuba(std::deque<std::int16_t>& num1,
std::deque<std::int16_t>& num2){
	if(num1.size() == 1 || num2.size() == 1){
		return multiply(num1, num2);
	}
	
	std::deque<std::int16_t> a, b, c, d;
	std::deque<std::int16_t> sum1, sum2;
	std::deque<std::int16_t> z0, z1, z2, res;
	std::size_t size, multiplier;
	
	size = std::max(num1.size(), num2.size());
	multiplier = size / 2 + size % 2;
	
	while(num1.size() < num2.size()){
		num1.push_front(0);
	}
	while(num2.size() < num1.size()){
		num2.push_front(0);
	}
	
	split(num1, a, b);
	split(num2, c, d);
	
	z0 = karatsuba(a, c);
	z1 = karatsuba(b, d);
	
	sum1 = addition(a, b);
	sum2 = addition(c, d);
	z2 = karatsuba(sum1, sum2);
	
	z2 = subtraction(z2, addition(z0, z1));
	
	z0 = multiply10(z0, 2 * multiplier);
	z2 = multiply10(z2, multiplier);
	
	res = addition(z0, addition(z1, z2));
	return res;
}
