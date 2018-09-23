#pragma once
#include "stdafx.h"
#include "Strategy.cpp"

class Spiteful : public Strategy
{
public:

	bool opponent_has_defected = false;

	bool choose_action()
	{
		if (opponents_last_moves.empty())
		{
			opponent_has_defected = false;
			return true;
		}

		if (!opponents_last_moves.back())
		{
			opponent_has_defected = true;
		}

		return !opponent_has_defected;
	}

};
