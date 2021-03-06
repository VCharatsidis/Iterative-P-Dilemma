// Iterative Preasoners Dilema.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Simulator.cpp"
#include "stdafx.h"
#include "Defector.cpp"
#include "Babinos.cpp"
#include "Tit_for_tat.cpp"
#include "One_two.cpp"
#include "Random.cpp"
#include "Strategy.cpp"
#include <iostream>
#include <string>


int main()
{
	Strategy* defector = new Defector();
	Strategy* thimas = new Babinos();
	Strategy* tit_f_tat = new Tit_for_Tat();
	Strategy* one_two = new One_For_U_2_For_Me();
	Strategy* randomer = new Random(0.5);
	Strategy* pirate = new Random(0.9);
	Strategy* optimist = new Random(0.1);

	Simulator sim =  Simulator();
	
	double res[2];

	double* result = sim.play_round(thimas, pirate, res);
	std::cout << "babinos "+ std::to_string(*result) + " pirate "+ std::to_string(*(result +1)) << std::endl;

	result = sim.play_round(tit_f_tat, defector, res);
	std::cout << "tit_tat " + std::to_string(*result) + " defector " + std::to_string(*(result + 1)) << std::endl;

	result = sim.play_round(randomer, defector, res);
	std::cout << "randomer " + std::to_string(*result) + " defector " + std::to_string(*(result + 1)) << std::endl;

	result = sim.play_round(randomer, pirate, res);
	std::cout << "randomer " + std::to_string(*result) + " pirate " + std::to_string(*(result + 1)) << std::endl;

	result = sim.play_round(thimas, one_two, res);
	std::cout << "babinos " + std::to_string(*result) + " one_two " + std::to_string(*(result + 1)) << std::endl;

	result = sim.play_round(one_two, defector, res);
	std::cout << "one_two " + std::to_string(*result) + " defector " + std::to_string(*(result + 1)) << std::endl;

	std::cout << "" << std::endl;
	std::cout << "Tournament results" << std::endl;
	std::cout << "" << std::endl;

	sim.tour();

	getchar();
    return 0;
}

