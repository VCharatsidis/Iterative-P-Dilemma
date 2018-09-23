#pragma once
#include "stdafx.h"
#include "Strategy.cpp"

class Tit_for_Tat : public Strategy
{
public:

	bool choose_action()
	{
		if (opponents_last_moves.empty())
		{
			return true;
		}
		else
		{
			return  opponents_last_moves.back();
		}
	}

};
