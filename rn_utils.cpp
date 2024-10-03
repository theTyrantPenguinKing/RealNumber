#include "rn_utils.hpp"

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

std::deque<std::int16_t> multiply(const std::deque<std::int16_t>& num1,
const std::deque<std::int16_t>& num2){
	std::deque<std::int16_t> result, aux;
	std::deque<std::int16_t>::const_reverse_iterator it1, it2;
	std::int16_t val, carry = 0;
	std::size_t shift = 0;
	
	result.push_front(0);
	
	for(it2 = num2.rbegin(); it2 != num2.rend(); it2++, shift++){
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
	
	return result;
}
