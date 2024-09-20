#include <iostream>
#include "realnumber.hpp"

using namespace std;

int main(){
	RealNumber r;
	std::size_t scale = 5;
	
	cout << "Ingrese un número real: ";
	cin >> r;
	
	cout << r << endl;
	
	cout << "Número positivo más pequeño con la escala: " << scale << ": " << RealNumber::getSmallest(scale) << endl;
	
	return 0;
}
