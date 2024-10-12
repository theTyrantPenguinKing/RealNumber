#include "realnumber.hpp"
#include <iostream>

using namespace std;

int main(){
	RealNumber num1, num2, prod;
	cout << "Enter a real number: ";
	cin >> num1;
	
	cout << "Enter another real number: ";
	cin >> num2;
	
	prod = num1 * num2;
	cout << num1 << " x " << num2 << " = " << prod << endl;
	
	return 0;
}
