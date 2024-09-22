#include "rn_subtraction.hpp"

std::deque<std::uint16_t> complement(const std::deque<std::uint16_t>& num){
	std::deque<std::uint16_t> res;
	std::deque<std::uint16_t>::const_reverse_iterator iter;
	iter = num.rbegin();
	
	for(; iter != num.rend() && *iter == 0; iter++){
		res.push_front(*iter);
	}
	if(iter != num.rend()){
		res.push_front(10 - *iter);
		iter++;
		
		for(; iter != num.rend(); iter++){
			res.push_front(10 - (*iter + 1));
		}
	}else{
		res.push_front(1);
	}
	
	return res;
}

std::deque<uint16_t> subtraction(const std::deque<std::uint16_t>& n1, const std::size_t scale1,
const std::deque<std::uint16_t>& n2, const std::size_t scale2){
	std::deque<std::uint16_t> res, aux;
	
	std::deque<std::uint16_t>::const_reverse_iterator it1, it2;
	
	aux = complement(n2);
	
	while(aux.size() - scale2 < n1.size() - scale1){
		aux.push_front(9);
	}
	
	it1 = n1.rbegin();
	it2 = aux.rbegin();
	
	if(scale1 > scale2){
		std::size_t dif = scale1 - scale2;
		for(std::size_t i = 0; i < dif && it1 != n1.rend(); i++, it1++){
			res.push_front(*it1);
		}
	}else if(scale2 > scale1){
		std::size_t dif = scale2 - scale1;
		for(std::size_t i = 0; i < dif && it2 != aux.rend(); i++, it2++){
			res.push_front(*it2);
		}
	}
	
	std::uint16_t carry = 0, val;
	for(; it1 != n1.rend() && it2 != aux.rend(); it1++, it2++){
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
	
	for(; it2 != aux.rend(); it2++){
		val = *it2 + carry;
		if(val > 9){
			carry = 1;
			val %= 10;
		}else{
			carry = 0;
		}
		res.push_front(val);
	}
	
	if(!carry){
		res = complement(res);
	}
	
	return res;
}