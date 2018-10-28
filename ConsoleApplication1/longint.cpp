//developed by Oleksandr Maystrenko K-22, 2018
#include <iostream>
#include "lab2_verylongint.hxx"
#include "lab2_functions.hxx"

VeryLongInt* (*VeryLongInt::multiply) (VeryLongInt, VeryLongInt) = nullptr;

VeryLongInt::VeryLongInt(int n0, int base0, int seed = 0) :VeryLongInt() {
	setN(n0);
	setBase(base0);
	if (seed != 0) {
		for (int i = 0; i < n; ++i) {
			setDigit(i, rand() % getBase());
		}
		while (getDigit(n - 1) == 0) {
			setDigit(n - 1, rand() % getBase());
		}
	}
}

int VeryLongInt::getN() {
	return n;
}
int VeryLongInt::getBase() {
	return base;
}
int VeryLongInt::getDigit(int i) {
	return number[i];
}
void VeryLongInt::setN(int n0) {
	n = n0;
}
void VeryLongInt::setBase(int base0) {
	base = base0;
}
void VeryLongInt::setDigit(int i, int x) {
	number[i] += x;
}
void VeryLongInt::setMultiply(VeryLongInt* (*multiply0) (VeryLongInt, VeryLongInt)) {
	multiply = multiply0;
}

VeryLongInt& VeryLongInt::operator= (VeryLongInt &a) {
	int an = a.getN();
	for (int i = 0; i < an; ++i)
		this->setDigit(i, a.getDigit(i));
	return *this;
}
VeryLongInt* VeryLongInt::operator+ (VeryLongInt a) {
	int base = this->getBase();
	int nAns = 1, n0 = std::max(this->getN(), a.getN());
	VeryLongInt *ans = new VeryLongInt(nAns, base);
	for (int i = 0; i < n0; ++i) {
		ans->setDigit(i, this->getDigit(i) + a.getDigit(i));
		if (ans->getDigit(i) >= base) {
			ans->setDigit(i, -base);
			ans->setDigit(i + 1, 1);
		}
		++nAns;
	}
	ans->setN(nAns);
	ans->checkLastDigit();
	return ans;
}
VeryLongInt* VeryLongInt::operator* (VeryLongInt a) {
	return multiply(*this, a);
}

VeryLongInt* VeryLongInt::basicMultiply(VeryLongInt a) {
	int base0 = this->getBase();
	int nAns = 0, d = 0;
	VeryLongInt *ans = new VeryLongInt(nAns, base0);
	VeryLongInt *lead = (this->getN() > a.getN()) ? this : &a;
	VeryLongInt *other = (this->getN() > a.getN()) ? &a : this;
	int nl = lead->getN();
	int no = other->getN();
	for (int i = 0; i < nl; ++i) {
		VeryLongInt *temp = new VeryLongInt(no, base0);
		temp = other->multiplyByDigit(lead->getDigit(i));
		ans = *ans + *temp->multiplyByBasePow(d);
		++d;
	}
	int j = notABigNumber;
	bool check = true;
	while (check) {
		if (ans->getDigit(j) == 0) {
			check = false;
			nAns = j;
		}
		--j;
	}
	for (int i = 0; i < nAns; ++i) {
		while (ans->getDigit(i) >= base0) {
			ans->setDigit(i, -base0);
			ans->setDigit(i + 1, 1);
		}
	}
	ans->setN(nAns);
	ans->checkLastDigit();
	return ans;
}
VeryLongInt* VeryLongInt::multiplyByDigit(int k) {
	int n = getN();
	int base = getBase();
	VeryLongInt *ans = new VeryLongInt(n, base);
	for (int i = 0; i < n; ++i) {
		ans->setDigit(i, getDigit(i)*k);
		while (ans->getDigit(i) >= base) {
			ans->setDigit(i, -base);
			ans->setDigit(i + 1, 1);
		}
	}
	ans->setN(n + 1);
	ans->checkLastDigit();
	return ans;
}
VeryLongInt* VeryLongInt::multiplyByBasePow(int k) {
	int n = getN();
	int base = getBase();
	VeryLongInt *ans = new VeryLongInt(n + k, base);
	for (int i = k; i < k + n; ++i)
		ans->setDigit(i, getDigit(i - k));
	ans->checkLastDigit();
	return ans;
}

VeryLongInt* VeryLongInt::getFirst(int k) {
	int base = getBase();
	VeryLongInt *ans = new VeryLongInt(k, base);
	for (int i = 0; i < k; ++i)
		ans->setDigit(i, getDigit(i));
	ans->checkLastDigit();
	return ans;
}
VeryLongInt* VeryLongInt::getWithoutFirst(int k) {
	int n = getN();
	int base = getBase();
	VeryLongInt *ans = new VeryLongInt(n - k, base);
	for (int i = 0; i < n; ++i)
		ans->setDigit(i, getDigit(i + k));
	ans->checkLastDigit();
	return ans;
}

void VeryLongInt::output() {
	for (int i = 0; i < n; ++i) {
		std::cout << number[n - i - 1] << "_";
	}
	std::cout << "\b \b";
}
void VeryLongInt::checkLastDigit() {
	int n0 = getN() - 1;
	if (getDigit(n0) == 0)
		setN(n0);
}