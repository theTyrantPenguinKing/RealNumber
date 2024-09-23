#include <iostream>
#include "realnumber.hpp"

using namespace std;

int main(){
	RealNumber r, s;
	
	cout << "Ingrese un número real: ";
	cin >> r;
	
	cout << "Ingrese otro número real: ";
	cin >> s;
	
	cout << r << " + " << s << " = " << r + s << endl;
	
	cout << r << " - " << s << " = " << r - s << endl;
	
	cout << s << " - " << r << " = " << s - r << endl;
	
	return 0;
}
