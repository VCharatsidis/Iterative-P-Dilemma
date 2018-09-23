#pragma once
#include "stdafx.h"
#ifndef RANDOM_H
#define RANDOM_H
#include "Strategy.cpp"
#include <algorithm>
#include <functional>
#include <random>

class Random : public Strategy
{
public:

	Random(double prob) : prob(prob) {}

	double prob;
	bool choose_action()
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_real_distribution<double> unif(0, 1);

		double coop = unif(eng);

		if (coop > prob)
		{
			return true;
		}
		else {
			return false;
		}
	}

};
#endif
