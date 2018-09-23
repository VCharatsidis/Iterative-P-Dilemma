
#pragma once
#include "stdafx.h"
#include "Strategy.cpp"

class Defector : public Strategy
{
public:

	bool choose_action()
	{
		return false;
	}

};
