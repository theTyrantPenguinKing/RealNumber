#ifndef RN_ADDITION_H
#define RN_ADDITION_H

#include <deque>
#include <cinttypes>
#include <iterator>

/*
 * Devuelve la suma de los dos números reales representados por los std::deque.
 * 
 * PRE: los números tienen la misma cantidad de dígitos después del punto
 * decimal
 *
 * Costo del algoritmo: O(max(n, m)) donde n y m son la cantidad de dígitos de
 * ambos números
 */
std::deque<std::uint16_t> addition(const std::deque<std::uint16_t>&,
const std::deque<std::uint16_t>&);

#endif
