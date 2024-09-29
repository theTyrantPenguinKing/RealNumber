#ifndef RN_SUBTRACTION_HPP
#define RN_SUBTRACTION_HPP

#include <deque>
#include <cinttypes>
#include <iterator>

/*
 * Devuelve el complemento a 10 del número
 */
std::deque<std::uint16_t> complement(const std::deque<std::uint16_t>&);

/*
 * Devuelve la resta de dos números reales representados por los std::deque.
 * 
 * PRE: los números tienen la misma cantidad de dígitos
 *
 * Costo del algoritmo: O(max(n, m)) donde n y m son la cantidad de dígitos de
 * ambos números
 */
std::deque<std::uint16_t> subtraction(const std::deque<std::uint16_t>&,
const std::deque<std::uint16_t>&);

#endif
