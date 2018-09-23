#pragma once
#include "stdafx.h"
#ifndef STRATEGY_H
#define STRATEGY_H
#include <vector>

class Strategy
{
public: 
	
	bool last_move;

	std::vector<bool> opponents_last_moves;

	Strategy()
	{
	}
	virtual bool choose_action() = 0;
};

#endif
