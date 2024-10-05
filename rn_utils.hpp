#ifndef RN_UTILS_HPP
#define RN_UTILS_HPP

#include <deque>
#include <cinttypes>
#include <iterator>

/*
Compares the absolute value of two numbers

returns 1 if the first number is greater than the second
returns 0 if the first number is equal to the second
return -1 if the first is less than the second
*/
std::int16_t compare(const std::deque<std::int16_t>&,
const std::deque<std::int16_t>&);

/*
Removes leading zeros
*/
std::deque<std::int16_t> removeLeadingZeros(const std::deque<std::int16_t>&);

/*
Splits the number in halves
PRE: the number has at least two digits
*/
void split(const std::deque<std::int16_t>&, std::deque<std::int16_t>&,
std::deque<std::int16_t>&);

/*
Returns the sum of the numbers ignoring their signs
PRE: the numbers have the same amount of digits after the decimal point
*/
std::deque<std::int16_t> addition(const std::deque<std::int16_t>&,
const std::deque<std::int16_t>&);

/*
Returns the difference of the numbers ignoring their signs
PRE: the numbers have the same amount of digits after decimal point
*/
std::deque<std::int16_t> subtraction(const std::deque<std::int16_t>&,
const std::deque<std::int16_t>&);

/*
Returns the multiplication of the two numbers
*/
std::deque<std::int16_t> multiply(const std::deque<std::int16_t>&,
const std::deque<std::int16_t>&);

#endif
