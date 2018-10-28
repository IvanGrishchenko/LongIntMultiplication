#include <iostream>
#include "longint.h"
#include "functions.h"

using namespace std;

int main() {
	try {

		VeryLongInt *myNumber1 = new VeryLongInt(8, 10, 5);
		VeryLongInt *myNumber2 = new VeryLongInt(8, 10, 17);
		VeryLongInt::setMultiply(karatsuba);

		myNumber1->output();
		cout << endl << endl;
		myNumber2->output();
		cout << endl << endl;

		VeryLongInt *myNumber3 = (*myNumber1)*(*myNumber2);

		myNumber3->output();
		cout << endl << endl;

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