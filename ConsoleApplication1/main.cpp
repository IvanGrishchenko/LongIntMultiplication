#include <iostream>
#include "longint.h"
#include "functions.h"

using namespace std;

int main() {
	try {

		LongInt *myNumber1 = new LongInt(8, 10, 4);
		LongInt *myNumber2 = new LongInt(8, 10, 16);
		LongInt::setMultiply(karatsuba);

		myNumber1->output();
		cout << endl << endl;
		myNumber2->output();
		cout << endl << endl;

		LongInt *myNumber3 = (*myNumber1)*(*myNumber2);

		myNumber3->output();
		cout << endl << endl;

		cout << RabinMillerTest(3571, 10);
		cout << endl;

		cout << SoloveyStrassen(97, 10);
		cout << endl;

		
		delete myNumber1;
		delete myNumber2;
	}
	catch (exception &e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "Unknown error occured" << endl;
	}
	
	return 0;
}