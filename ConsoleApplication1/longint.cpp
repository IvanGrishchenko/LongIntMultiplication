#define NOMINMAX
#include <iostream>
#include <algorithm>
#include <windows.h>
#include "longint.h"
#include "functions.h"

LongInt* (*LongInt::multiply) (LongInt, LongInt) = nullptr;

LongInt::LongInt(int n0, int base0, int seed = 0) :LongInt() {
	setN(n0);
	setBase(base0);
	if (seed != 0) 
	{
		for (int i = 0; i < n; ++i) 
		{
			setDigit(i, rand() % getBase());
		}
		while (getDigit(n - 1) == 0) 
		{
			setDigit(n - 1, rand() % getBase());
		}
	}
}

int LongInt::getN() {
	return n;
}
int LongInt::getBase() {
	return base;
}
int LongInt::getDigit(int i) {
	return number[i];
}
void LongInt::setN(int n0) {
	n = n0;
}
void LongInt::setBase(int base0) {
	base = base0;
}
void LongInt::setDigit(int i, int x) {
	number[i] += x;
}
void LongInt::setMultiply(LongInt* (*multiply0) (LongInt, LongInt)) {
	multiply = multiply0;
}

LongInt& LongInt::operator= (LongInt &a) {
	int an = a.getN();
	for (int i = 0; i < an; ++i)
		this->setDigit(i, a.getDigit(i));
	return *this;
}
LongInt* LongInt::operator+ (LongInt a) {
	int base = this->getBase();
	int nAns = 1, n0 = std::max(this->getN(), a.getN());
	LongInt *ans = new LongInt(nAns, base);
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
LongInt* LongInt::operator* (LongInt a) {
	return multiply(*this, a);
}

LongInt* LongInt::basicMultiply(LongInt a) {
	int base0 = this->getBase();
	int nAns = 0, d = 0;
	LongInt *ans = new LongInt(nAns, base0);
	LongInt *lead = (this->getN() > a.getN()) ? this : &a;
	LongInt *other = (this->getN() > a.getN()) ? &a : this;
	int nl = lead->getN();
	int no = other->getN();
	for (int i = 0; i < nl; ++i) {
		LongInt *temp = new LongInt(no, base0);
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
LongInt* LongInt::multiplyByDigit(int k) {
	int n = getN();
	int base = getBase();
	LongInt *ans = new LongInt(n, base);
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
LongInt* LongInt::multiplyByBasePow(int k) 
{
	int n = getN();
	int base = getBase();
	LongInt *ans = new LongInt(n + k, base);
	for (int i = k; i < k + n; ++i)
		ans->setDigit(i, getDigit(i - k));
	ans->checkLastDigit();
	return ans;
}

LongInt* LongInt::getFirst(int k) {
	int base = getBase();
	LongInt *ans = new LongInt(k, base);
	for (int i = 0; i < k; ++i)
		ans->setDigit(i, getDigit(i));
	ans->checkLastDigit();
	return ans;
}
LongInt* LongInt::getWithoutFirst(int k) {
	int n = getN();
	int base = getBase();
	LongInt *ans = new LongInt(n - k, base);
	for (int i = 0; i < n; ++i)
		ans->setDigit(i, getDigit(i + k));
	ans->checkLastDigit();
	return ans;
}

void LongInt::output() {
	for (int i = 0; i < n; ++i) {
		std::cout << number[n - i - 1] << "_";
	}
	std::cout << "\b \b";
}
void LongInt::checkLastDigit() {
	int n0 = getN() - 1;
	if (getDigit(n0) == 0)
		setN(n0);
}