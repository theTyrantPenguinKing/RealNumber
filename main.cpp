#include "realnumber.hpp"
#include <iostream>

using namespace std;

int main(){
	RealNumber num1, num2;
	
	std::cout << "Enter a real number: ";
	cin >> num1;
	
	std::cout << "Enter another real number: ";
	cin >> num2;
	
	cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;
	
	cout << num1 << " - " << num2 << " = " << num1 - num2 << endl;
	
	cout << num2 << " - " << num1 << " = " << num2 - num1 << endl;
	
	return 0;
}
