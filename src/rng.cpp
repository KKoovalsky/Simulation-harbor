/********************************************//**
 * \file   	rng.cpp
 * \author	Krzysztof Bakowski
 ***********************************************/

#include "sc.h"

const int q = 127773;
const int r = 2836;
const int range = 2147483647; //2^31-1

double Uniform(int& x)
{
	register int h = int(x / q);

	x = 16807 * (x - q * h) - r * h;

	if (x < 0) x += range;

	return static_cast<long double>(x) / static_cast<long double>(range);
}
