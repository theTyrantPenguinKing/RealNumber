#include <iostream>
#include "realnumber.hpp"

using namespace std;

int main(){
	RealNumber r, s;
	
	cout << "Ingrese un número real: ";
	cin >> r;
	
	cout << "Ingrese otro número real: ";
	cin >> s;
	
	if(r == s){
		cout << r << " == " << s << endl;
	}
	
	if(r != s){
		cout << r << " != " << s << endl;
	}
	
	if(r < s){
		cout << r << " < " << s << endl;
	}
	
	if(r <= s){
		cout << r << " <= " << s << endl;
	}
	
	if(r > s){
		cout << r << " > " << s << endl;
	}
	
	if(r >= s){
		cout << r << " >= " << s << endl;
	}
	
	return 0;
}
