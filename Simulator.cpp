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
#include "two_one.cpp"

#include "Strategy.cpp"
#include <vector>
#include <map>
#include <iostream>
#include <string>


class Simulator
{
public:
	int rounds = 5000;
	bool noisy = false;
	double chanse_to_change = 0.9;

	std::map<int, double> avg_scores{
		{ 0, 0 },
		{ 1, 0 },
		{ 2, 0 },
		{ 3, 0 },
		{ 4, 0 },
		{ 5, 0 },
		{ 6, 0 },
		{ 7, 0 },
		{ 8, 0 },
		{ 9, 0 },
		{10,0}
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
		Strategy* two_one = new Two_one();

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
		strats.push_back(two_one);

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
	
		std::vector<int> to_exclude = { 1, 2, 3 };

		for (int strat = 0; strat < strats.size(); strat++)
		{
			std::cout << "" << std::endl;
			for (int other_strat = strat; other_strat < strats.size(); other_strat++)
			{
				if (exclude(to_exclude, strat) || exclude(to_exclude, other_strat))
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
		double normalize = (strats.size() - to_exclude.size()-1) ;

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
		std::cout << "two_one " + std::to_string(avg_scores.at(10) / normalize) << std::endl;

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

		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_real_distribution<double> unif(0, 1);

		for (int round = 0; round < rounds; round++)
		{
			bool action1 = strat1->choose_action();
			bool action2 = strat2->choose_action();

			if (noisy)
			{
				double change1 = unif(eng);
				

				if (change1 > chanse_to_change)
				{
					action1 = !action1;
				}

				double change2 = unif(eng);

				if (change2 > chanse_to_change)
				{
					action2 = !action2;
				}
				
			}

			rewords_1 += rewords[action1][action2][0];
			rewords_2 += rewords[action1][action2][1];

			strat1->opponents_last_moves.push_back(action2);
			strat2->opponents_last_moves.push_back(action1);

		}

		avg_reword[0] = rewords_1 / rounds;
		avg_reword[1] = rewords_2 / rounds;
		
		return avg_reword;
	}

	bool exclude(std::vector<int> to_exclude, int current)
	{
		for (int i = 0; i < to_exclude.size(); i++)
		{
			if (to_exclude[i] == current)
			{
				return true;
			}
		}

		return false;
	}

};