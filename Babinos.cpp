#pragma once
#include "stdafx.h"
#ifndef BABINOS_H
#define BABINOS_H
#include "Strategy.cpp"

class Babinos : public Strategy
{
public:
	bool eimai_thimas = true;

	bool choose_action()
	{
		return eimai_thimas;
	}

};

#endif
