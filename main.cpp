#include <iostream>
#include "realnumber.hpp"

using namespace std;

int main(){
	RealNumber r, s, suma;
	
	cout << "Ingrese un número real: ";
	cin >> r;
	
	cout << "Ingrese otro número real: ";
	cin >> s;
	
	suma = r + s;
	cout << r << " + " << s << " = " << suma << endl;
	
	cout << "Número redondeado a dos dígitos después del punto decimal: " << suma.round(2) << std::endl;
	
	return 0;
}
