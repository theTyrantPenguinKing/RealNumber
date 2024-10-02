#include "realnumber.hpp"
#include <iostream>

using namespace std;

int main(){
	RealNumber num1, num2, sum, subt;
	
	cout << "Enter a real number: ";
	cin >> num1;
	
	cout << "Enter another real number: ";
	cin >> num2;
	
	sum = num1 + num2;
	cout << num1 << " + " << num2 << " = " << sum << endl;
	
	subt = num1 - num2;
	cout << num1 << " - " << num2 << " = " << subt << endl;
	
	subt = num2 - num1;
	cout << num2 << " - " << num1 << " = " << subt << endl;
	
	return 0;
}
