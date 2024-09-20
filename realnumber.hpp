#ifndef REALNUMBER_H
#define REALNUMBER_H

#include <iostream>
#include <cinttypes>
#include <deque>
#include <string>
#include <cctype>
#include <iterator>

const std::size_t DEFAULT_MAX_SCALE = 9;

class RealNumber{
	// sobrecarga del operador de inserción de flujo
	friend std::ostream& operator<<(std::ostream&, const RealNumber&);
	
	// sobrecarga del operador de extracción de flujo
	friend std::istream& operator>>(std::istream&, RealNumber&);
	
	// devuelve 0 si los números son iguales, 1 si el primero es mayor al segundo
	// y -1 si el primero es menor al segundo
	friend int16_t compare(const RealNumber&, const RealNumber&);
	
	// sobrecargas del operador de igualdad
	friend bool operator==(const std::int64_t, const RealNumber&);
	friend bool operator==(const std::string&, const RealNumber&);
	
	// sobrecargas del operador de desigualdad
	friend bool operator!=(const std::int64_t, const RealNumber&);
	friend bool operator!=(const std::string&, const RealNumber&);
	
	// sobrecargas del operador menor que
	friend bool operator<(const std::int64_t, const RealNumber&);
	friend bool operator<(const std::string&, const RealNumber&);
	
	// sobrecargas del operador menor o igual que
	friend bool operator<=(const std::int64_t, const RealNumber&);
	friend bool operator<=(const std::string&, const RealNumber);
	
	// sobrecargas del operador mayor que
	friend bool operator>(const std::int64_t, const RealNumber&);
	friend bool operator>(const std::string&, const RealNumber&);
	
	// sobrecargas del operador mayor o igual que
	friend bool operator>=(const std::int64_t, const RealNumber&);
	friend bool operator>=(const std::string&, const RealNumber);
	
	private:
		// contiene los dígitos del número real
		std::deque<uint16_t> digits;
		// signo del número real
		std::int16_t sign;
		// cantidad de dígitos después del punto decimal
		std::size_t scale;
		// cantidad máxima de dígitos después del punto decimal
		static std::size_t maxScale;
		
		// elimina ceros innecesarios al comienzo y final del número real
		void trimRealNumber();
		
		// agrega ceros al comienzo del número
		void addLeadingZeros(const std::size_t);
		
		// agrega ceros al final del número
		void addEndingZeros(const std::size_t);
		
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
		
		// modifica la cantidad máxima de dígitos después del punto decimal
		static void setMaxScale(const std::size_t);
		
		// devuelve el número real positivo más pequeño posible con la
		// escala pasada como parámetro
		static RealNumber getSmallest(const std::size_t);
		
		// sobrecarga del operador de igualdad
		bool operator==(const RealNumber&) const ;
		
		// sobrecarga del operador de desigualdad
		bool operator!=(const RealNumber&) const ;
		
		// sobrecarga del operador menor que
		bool operator<(const RealNumber&) const;
		
		// sobrecarga del operador menor o igual que
		bool operator<=(const RealNumber&) const ;
		
		// sobrecarga del operador mayor que
		bool operator>(const RealNumber&) const ;
		
		// sobrecarga del operador mayor o igual que
		bool operator>=(const RealNumber&) const ;
		
		// retorna una copia del valor absoluto del número
		RealNumber absolute() const ;
		
		// retorna una copia del opuesto del número
		RealNumber operator-() const ;
};

#endif
