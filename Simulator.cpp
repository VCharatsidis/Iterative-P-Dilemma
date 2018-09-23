#pragma once
#include "stdafx.h"
#include "Defector.cpp"
#include "Babinos.cpp"
#include "Tit_for_tat.cpp"
#include "One_two.cpp"
#include "Random.cpp"
#include "Win_stay_lose_shift.cpp"
#include "Smart_thief.cpp"
#include "Spiteful.cpp"

#include "Strategy.cpp"
#include <vector>
#include <map>
#include <iostream>
#include <string>


class Simulator
{
public:
	int rounds = 3000;

	double defector_avg;
	double thimas_avg;
	double tit_f_tat_avg;
	double one_two_avg;
	double randomer_avg;
	double pirate_avg;
	double opportunist_avg;
	double win_stay_lose_shift_avg;
	double smart_thief_avg;
	double spiteful_avg;

	std::map<int, double> avg_scores{
		{ 0, defector_avg },
		{ 1, pirate_avg },
		{ 2, randomer_avg },
		{ 3, opportunist_avg },
		{ 4, tit_f_tat_avg },
		{ 5, one_two_avg },
		{ 6, thimas_avg },
		{ 7, win_stay_lose_shift_avg},
		{ 8, smart_thief_avg},
		{ 9, spiteful_avg}
	};

	int rewords[2][2][2];


	Simulator()
	{
		int temptation = 5;
		int reword = 3;
		int punishment = 1;
		int sucker = 0;

		rewords[0][0][0] = punishment;
		rewords[0][0][1] = punishment;

		rewords[0][1][0] = temptation;
		rewords[0][1][1] = sucker;

		rewords[1][0][0] = sucker;
		rewords[1][0][1] = temptation;

		rewords[1][1][0] = reword;
		rewords[1][1][1] = reword;
	}

	void tour()
	{
		Strategy* defector = new Defector();
		Strategy* thimas = new Babinos();
		Strategy* tit_f_tat = new Tit_for_Tat();
		Strategy* one_two = new One_For_U_2_For_Me();

		Strategy* randomer = new Random(0.5);
		Strategy* pirate = new Random(0.9);
		Strategy* opportunist = new Random(0.1);

		Strategy* win_stay_lose_shift = new Win_stay_lose_shift();
		Strategy* smart_thief = new Smart_thief();
		Strategy* spiteful = new Spiteful();

		std::vector<Strategy*> strats;

		strats.push_back(defector);
		strats.push_back(pirate);
		strats.push_back(randomer);
		strats.push_back(opportunist);

		strats.push_back(tit_f_tat);
		strats.push_back(one_two);
		strats.push_back(thimas);
		strats.push_back(win_stay_lose_shift);
		strats.push_back(smart_thief);
		strats.push_back(spiteful);

		//{ 0, defector_avg },
		//{ 1, pirate_avg },
		//{ 2, randomer_avg },
		//{ 3, opportunist_avg },

		//{ 4, tit_f_tat_avg },
		//{ 5, one_two_avg },
		//{ 6, thimas_avg },
		//{ 7, win_stay_lose_shift_avg },
		//{ 8, smart_thief_avg },
		//{ 9, spiteful_avg }
		double count_rouds = 0;
		int excluded_strats = 4;

		for (int strat = 0; strat < strats.size(); strat++)
		{
			if (strat == 2)
			{
				continue;
			}
			if (strat == 3)
			{
				continue;
			}

			for (int other_strat = strat; other_strat < strats.size(); other_strat++)
			{
				if (other_strat == strat)
				{
					continue;
				}

				//exclude some strats from tour
				if (other_strat == 1 || strat == 1)
				{
					continue;
				}
				if (other_strat ==6 || strat ==6)
				{
					continue;
				}
				if (other_strat == 2 )
				{
					continue;
				}
				if (other_strat == 3 )
				{
					continue;
				}
				
				std::cout << "strat " + std::to_string(strat) + " other_strat " + std::to_string(other_strat) << std::endl;

				double res[2];
				double* result = play_round(strats.at(strat), strats.at(other_strat), res);

				avg_scores[strat] = avg_scores.at(strat) + *result;
				avg_scores[other_strat] = avg_scores.at(other_strat) + *(result + 1);

				count_rouds++;
			}
		}
		double normalize = (strats.size() - excluded_strats-1) ;
		std::cout << "normalize " + std::to_string(normalize) << std::endl;
		std::cout << "rounds of tournament " + std::to_string(count_rouds) << std::endl;

		std::cout << "defector " + std::to_string(avg_scores.at(0) / normalize) << std::endl;
		std::cout << "pirate " + std::to_string(avg_scores.at(1) / normalize) << std::endl;
		std::cout << "randomer " + std::to_string(avg_scores.at(2)  / normalize) << std::endl;
		std::cout << "oportunist " + std::to_string(avg_scores.at(3) / normalize) << std::endl;

		std::cout << "tit_for_tat " + std::to_string(avg_scores.at(4) / normalize) << std::endl;
		std::cout << "one_two " + std::to_string(avg_scores.at(5)  /normalize) << std::endl;
		std::cout << "thimas " + std::to_string(avg_scores.at(6) / normalize) << std::endl;
		std::cout << "win_stay_lose_shift " + std::to_string(avg_scores.at(7) / normalize) << std::endl;
		std::cout << "smart thief " + std::to_string(avg_scores.at(8) / normalize) << std::endl;
		std::cout << "spiteful " + std::to_string(avg_scores.at(9) / normalize) << std::endl;

		//{ 0, defector_avg },
		//{ 1, pirate_avg },
		//{ 2, randomer_avg },
		//{ 3, opportunist_avg },

		//{ 4, tit_f_tat_avg },
		//{ 5, one_two_avg },
		//{ 6, thimas_avg },
		//{ 7, win_stay_lose_shift_avg },
		//{ 8, smart_thief_avg },
		//{ 9, spiteful_avg }
	}

	double* play_round(Strategy* strat1, Strategy* strat2, double avg_reword[])
	{
		double rewords_1 = 0;
		double rewords_2 = 0;

		strat1->opponents_last_moves.clear();
		strat2->opponents_last_moves.clear();

		for (int round = 0; round < rounds; round++)
		{
			bool action1 = strat1->choose_action();
			bool action2 = strat2->choose_action();

			rewords_1 += rewords[action1][action2][0];
			rewords_2 += rewords[action1][action2][1];

			strat1->opponents_last_moves.push_back(action2);
			strat2->opponents_last_moves.push_back(action1);

		}

		avg_reword[0] = rewords_1 / rounds;
		avg_reword[1] = rewords_2 / rounds;
		//std::cout << "defector " + std::to_string(rew[0]) + " babinos " + std::to_string(rew[1]) << std::endl;
		return avg_reword;
	}

};