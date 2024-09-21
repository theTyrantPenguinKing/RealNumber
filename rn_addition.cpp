#include "rn_addition.hpp"
#include <iostream>

std::deque<std::uint16_t> addition(const std::deque<std::uint16_t>& n1, const std::size_t scale1,
const std::deque<std::uint16_t>& n2, const std::size_t scale2){
	std::deque<std::uint16_t> res;
	std::deque<std::uint16_t>::const_reverse_iterator it1, it2;
	
	it1 = n1.rbegin();
	it2 = n2.rbegin();
	
	if(scale1 > scale2){
		std::size_t dif = scale1 - scale2;
		for(std::size_t i = 0; i < dif && it1 != n1.rend(); i++, it1++){
			res.push_front(*it1);
		}
	}else if(scale2 > scale1){
		std::size_t dif = scale2 - scale1;
		for(std::size_t i = 0; i < dif && it2 != n2.rend(); i++, it2++){
			res.push_front(*it2);
		}
	}
	
	std::uint16_t carry = 0, val;
	for(; it1 != n1.rend() && it2 != n2.rend(); it1++, it2++){
		val = *it1 + *it2 + carry;
		if(val > 9){
			carry = 1;
			val %= 10;
		}else{
			carry = 0;
		}
		res.push_front(val);
	}
	
	for(; it1 != n1.rend(); it1++){
		val = *it1 + carry;
		if(val > 9){
			carry = 1;
			val %= 10;
		}else{
			carry = 0;
		}
		res.push_front(val);
	}
	
	for(; it2 != n2.rend(); it2++){
		val = *it2 + carry;
		if(val > 9){
			carry = 1;
			val %= 10;
		}else{
			carry = 0;
		}
		res.push_front(val);
	}
	
	if(carry){
		res.push_front(carry);
	}
	
	if(res.empty()){
		res.push_front(0);
	}
	
	return res;
}