#ifndef REALNUMBER_H
#define REALNUMBER_H

#include <iostream>
#include <cinttypes>
#include <deque>
#include <string>
#include <cctype>
#include <iterator>

class RealNumber{
	// sobrecarga del operador de inserción de flujo
	friend std::ostream& operator<<(std::ostream&, const RealNumber&);
	
	// sobrecarga del operador de extracción de flujo
	friend std::istream& operator>>(std::istream&, RealNumber&);
	
	private:
		// contiene los dígitos del número real
		std::deque<uint16_t> digits;
		// signo del número real
		std::int16_t sign;
		// cantidad de dígitos después del punto decimal
		std::size_t scale;
		
		// elimina ceros innecesarios al comienzo y final del número real
		void trimRealNumber();
		
	public:
		// constructores
		RealNumber();
		RealNumber(const std::int64_t);
		RealNumber(const std::string&);
		RealNumber(const RealNumber&);
		
		// destructor
		~RealNumber();
		
		// sobrecargas del operador de asignación
		const RealNumber& operator=(const RealNumber&);
		const RealNumber& operator=(const std::int64_t);
		const RealNumber& operator=(const std::string&);
		
		// retorna un string que representa al número real
		std::string toString() const ;
		
		// devuelve la cantidad total de dígitos del número real
		std::size_t getPrecision() const ;
		
		// devuelve la cantidad total de dígitos después del punto decimal
		std::size_t getScale() const ;
};

#endif
