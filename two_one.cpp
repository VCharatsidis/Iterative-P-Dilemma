#pragma once
#include "stdafx.h"
#ifndef TWO_ONE_H
#define TWO_ONE_H
#include "Strategy.cpp"

class Two_one : public Strategy
{
public:
	bool last_opponent = true;
	bool choose_action()
	{
		int moves_played = opponents_last_moves.size();
		bool last;
		bool last2;

		if (moves_played > 1)
		{
			last = opponents_last_moves.at(moves_played - 1);
			last2 = opponents_last_moves.at(moves_played - 2);
		}
		else {
			return true;
		}

		if (!last || !last2)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};
#endif
