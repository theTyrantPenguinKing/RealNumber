#include "rn_utils.hpp"

std::deque<std::uint16_t> addLeadingZeros(const std::deque<std::uint16_t>& n,
const std::size_t zeros){
	std::deque<std::uint16_t> res = n;
	for(std::size_t i = 0; i < zeros; i++){
		res.push_front(0);
	}
	
	return res;
}

std::deque<std::uint16_t> addEndingZeros(const std::deque<std::uint16_t>& n,
const std::size_t zeros){
	std::deque<std::uint16_t> res = n;
	for(std::size_t i = 0; i < zeros; i++){
		res.push_back(0);
	}
	
	return res;
}

std::deque<std::uint16_t> smallestNumber(const std::size_t scale){
	std::deque<std::uint16_t> res;
	
	for(std::size_t i = 0; i < scale; i++){
		res.push_back(0);
	}
	if(res.empty()){
		res.push_back(0);
	}else{
		res.push_back(1);
	}
	
	return res;
}