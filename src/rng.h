/********************************************//**
 * \file   	rng.h
 * \brief	Deklaracja generatorow liczb losowych o rozk³adzie rownomiernym i wykladniczym.
 * \author	Krzysztof Bakowski
 ***********************************************/

#ifndef SRC_RNG_H_
#define SRC_RNG_H_

extern  const int q;
extern  const int r;
extern  const int range;

double Uniform(int& x);

inline double Exponential(double& lambda, int& x)
{
	return -log(Uniform(x)) / lambda;
}

#endif /* SRC_RNG_H_ */
