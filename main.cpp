#include <iostream>
#include "realnumber.hpp"

using namespace std;

int main(){
	RealNumber r;
	
	cout << "Ingrese un número real: ";
	cin >> r;
	
	cout << r << endl;
	cout << "Opuesto de " << r << ": " << -r << endl;
	cout << "Valor absoluto de " << r << ": " << r.absolute() << endl;
	
	return 0;
}
