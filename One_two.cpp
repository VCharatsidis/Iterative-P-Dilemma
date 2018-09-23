#pragma once
#include "stdafx.h"
#ifndef ONE_TWO_H
#define ONE_TWO_H
#include "Strategy.cpp"

class One_For_U_2_For_Me : public Strategy
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

		if (!last && !last2)
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
