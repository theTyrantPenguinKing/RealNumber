#ifndef RN_UTILS_HPP
#define RN_UTILS_HPP

#include <deque>
#include <cinttypes>

// agrega la cantidad especificada ceros al comienzo del número
std::deque<std::uint16_t> addLeadingZeros(const std::deque<std::uint16_t>&,
const std::size_t);

// agrega la cantidad especificada de ceros al final del número
std::deque<std::uint16_t> addEndingZeros(const std::deque<std::uint16_t>&,
const std::size_t);

// devuelve el número real más pequeño con la escala especificada
std::deque<std::uint16_t> smallestNumber(const std::size_t);

#endif