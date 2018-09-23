#pragma once
#include "stdafx.h"
#ifndef SMART_THIEF_H
#define SMART_THIEF_H
#include "Strategy.cpp"

class Smart_thief : public Strategy
{
public:

	bool choose_action()
	{
		int number_moves = opponents_last_moves.size();
		bool last_opponent_move;

		if (number_moves > 0)
		{
			last_opponent_move = opponents_last_moves.at(number_moves - 1);
		}
		else {
			return true;
		}

		if (last_move && last_opponent_move)
		{
			return false;
		}
		else if (last_move && !last_opponent_move)
		{
			return false;
		}
		else if (!last_move && last_opponent_move)
		{
			return false;
		}
		else if (!last_move && !last_opponent_move)
		{
			return true;
		}
	}
};
#endif
