/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#include "random_1.h"
#include <iostream>
#include <cmath>

double simpleMonteCarlo1(double expiry,
						 double strike,
						 double spot,
						 double vol,
						 double rate,
						 unsigned long numberOfPaths)
{

	double variance = vol*vol*expiry;
	double rootVariance = std::sqrt(variance);
	double itoCorrection = -0.5*variance;

	double movedSpot = spot*exp(rate * expiry +itoCorrection);
	double thisSpot;
	double runningSum=0;

	for (unsigned long i=0; i < numberOfPaths; i++)
	{
		double thisGaussian = getOneGaussianByBoxMuller();
		thisSpot = movedSpot * std::exp( rootVariance*thisGaussian);
		double thisPayoff = thisSpot - strike;
    	thisPayoff = thisPayoff > 0 ? thisPayoff : 0;
		runningSum += thisPayoff;
	}

	double mean = runningSum / numberOfPaths;
	mean *= std::exp(-rate * expiry);
	return mean;
}

int main()
{

	double expiry;
	double strike; 
	double spot; 
	double vol; 
	double rate;
	unsigned long numberOfPaths;

	std::cout << "\nEnter expiry\n";
	std::cin >> expiry;

	std::cout << "\nEnter strike\n";
	std::cin >> strike;

	std::cout << "\nEnter spot\n";
	std::cin >> spot;

	std::cout << "\nEnter vol\n";
	std::cin >> vol;

	std::cout << "\nr\n";
	std::cin >> rate;

	std::cout << "\nNumber of paths\n";
	std::cin >> numberOfPaths;

	double result = simpleMonteCarlo1(expiry,
                                      strike, 
							          spot, 
							          vol, 
							          rate, 
						              numberOfPaths);

	std::cout <<"the price is " << result << "\n";

    double tmp;
    std::cin >> tmp;

	return 0;
}
