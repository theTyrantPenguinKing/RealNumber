#include <iostream>
#include "realnumber.hpp"

using namespace std;

int main(){
	RealNumber r;
	
	cout << "Ingrese un número real: ";
	cin >> r;
	
	cout << r << endl;
	
	cout << "Precisión: " << r.getPrecision() << endl;
	cout << "Escala: " << r.getScale() << endl;
	
	return 0;
}
