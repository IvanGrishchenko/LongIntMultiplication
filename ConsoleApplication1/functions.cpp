#include <ctime>
#include "longint.h"
#include <algorithm>
#include <iostream>

#define ll long long

LongInt* karatsuba(LongInt x, LongInt y) {
	int xn = x.getN();
	int yn = y.getN();
	if (xn <= x.notABigNumber / 2 && yn <= y.notABigNumber / 2)
		return x.basicMultiply(y);
	LongInt *a, *b, *c, *d;
	int m = std::min(xn / 2 + xn % 2, yn / 2 + yn % 2);
	a = x.getWithoutFirst(xn + xn % 2 - m);
	b = x.getFirst(m);
	c = y.getWithoutFirst(yn + yn % 2 - m);
	d = y.getFirst(m);
	/*
	std::cout<<std::endl;
	a->output();
	std::cout<<std::endl;
	b->output();
	std::cout<<std::endl;
	c->output();
	std::cout<<std::endl;
	d->output();
	std::cout<<std::endl;
	*/
	LongInt *aTimesC = karatsuba(*a, *c);
	LongInt *bTimesD = karatsuba(*b, *d);
	LongInt *aTimesDPlusBTimesC = *(karatsuba(*a, *d)) + *(karatsuba(*b, *c));
	LongInt *ans = *(aTimesC->multiplyByBasePow(2 * m)) + *(aTimesDPlusBTimesC->multiplyByBasePow(m));
	ans = *ans + *bTimesD;
	ans->checkLastDigit();
	return ans;
}
LongInt* toomKuk(LongInt x, LongInt y) {
	return new LongInt(500, 10, 14);
}
LongInt* shenhage(LongInt x, LongInt y) {
	return new LongInt(500, 10, 14);
}
LongInt* shtrassen(LongInt x, LongInt y) {
	return new LongInt(500, 10, 14);
}


ll modpow(ll base, ll exp, ll modulus) {
	base %= modulus;
	ll result = 1;
	while (exp > 0) {
		if (exp & 1) result = (result * base) % modulus;
		base = (base * base) % modulus;
		exp >>= 1;
	}
	return result;
}


// тест Миллера — Рабина на простоту числа
// производится k раундов проверки числа n на простоту
bool RabinMillerTest(ll n, int k)
{
	// если n == 2 или n == 3 - эти числа простые, возвращаем true
	if (n == 2 || n == 3)
		return true;

	// если n < 2 или n четное - возвращаем false
	if (n < 2 || n % 2 == 0)
		return false;

	// представим n − 1 в виде (2^s)·t, где t нечётно, это можно сделать последовательным делением n - 1 на 2
	ll t = n - 1;

	int s = 0;

	while (t % 2 == 0)
	{
		t /= 2;
		s++;
	}

	// повторить k раз
	for (int i = 0; i < k; i++)
	{
		// выберем случайное целое число a в отрезке [2, n − 2]
		
		ll a;
		srand(time(0));
		a = 2 + rand() % (n - 2);

		/*
		std::cout << std::endl;
		std::cout<< " a = " << a << std::endl;
		*/
		

		// x ← a^t mod n, вычислим с помощью возведения в степень по модулю
		ll x = modpow(a, t, n);
		/*
		std::cout << std::endl;
		std::cout << " t = " << t << std::endl;
		std::cout << " x = " << x << std::endl;

		std::cout << std::endl;
		std::cout << "cycle is on and s = " << s << std::endl;
		*/

		// если x == 1 или x == n − 1, то перейти на следующую итерацию цикла
		if (x == 1 || x == n - 1)
			continue;

		// повторить s − 1 раз
		for (int r = 1; r < s; r++)
		{
			// x ← x^2 mod n
			x = modpow(x, 2, n);
			/*
			std::cout << std::endl;
			std::cout << " xin = " << x << std::endl;
			*/

			// если x == 1, то вернуть "составное"
			if (x == 1)
				return false;

			// если x == n − 1, то перейти на следующую итерацию внешнего цикла
			if (x == n - 1)
				break;
		}

		if (x != n - 1)
			return false;
	}

	// вернуть "вероятно простое"
	return true;
}

//Алгоритм вычисления символа Якоби
int calculateJacobian(ll a, ll n)
{
	if (!a)
		return 0;
	int ans = 1;
	ll temp;
	if (a < 0)
	{
		a = -a;
		if (n % 4 == 3)
			ans = -ans;
	}
	if (a == 1)
		return ans;
	while (a)
	{
		if (a < 0)
		{
			a = -a;
			if (n % 4 == 3)
				ans = -ans;
		}
		while (a % 2 == 0)
		{
			a = a / 2;
			if (n % 8 == 3 || n % 8 == 5)
				ans = -ans;
		}
		std::swap(a, n);
		if (a % 4 == 3 && n % 4 == 3)
			ans = -ans;
		a = a % n;
		if (a > n / 2)
			a = a - n;
	}
	if (n == 1)
		return ans;
	return 0;
}


bool SoloveyStrassen(ll n, int k)
{
	if (n < 2)
		return false;
	if (n != 2 && n % 2 == 0)
		return false;
	for (int i = 0; i < k; i++)
	{
		srand(time(0));
		ll a = rand() % (n - 1) + 1;
		ll jacobian = (n + calculateJacobian(a, n)) % n;
		ll mod = modpow(a, (n - 1) / 2, n);
		if (!jacobian || mod != jacobian)
		{
			return false;
		}
	}
	return true;
}