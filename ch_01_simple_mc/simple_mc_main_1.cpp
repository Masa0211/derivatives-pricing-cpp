/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#include "random_1.h"
#include <iostream>
#include <cmath>
using namespace std;

double SimpleMonteCarlo1(double expiry,
						 double strike,
						 double spot,
						 double vol,
						 double rate,
						 unsigned long numberOfPaths)
{

	double variance = vol*vol*expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;

	double movedSpot = spot*exp(rate * expiry +itoCorrection);
	double thisSpot;
	double runningSum=0;

	for (unsigned long i=0; i < numberOfPaths; i++)
	{
		double thisGaussian = getOneGaussianByBoxMuller();
		thisSpot = movedSpot * exp( rootVariance*thisGaussian);
		double thisPayoff = thisSpot - strike;
    	thisPayoff = thisPayoff > 0 ? thisPayoff : 0;
		runningSum += thisPayoff;
	}

	double mean = runningSum / numberOfPaths;
	mean *= exp(-rate * expiry);
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

	cout << "\nEnter expiry\n";
	cin >> expiry;

	cout << "\nEnter strike\n";
	cin >> strike;

	cout << "\nEnter spot\n";
	cin >> spot;

	cout << "\nEnter vol\n";
	cin >> vol;

	cout << "\nr\n";
	cin >> rate;

	cout << "\nNumber of paths\n";
	cin >> numberOfPaths;

	double result = SimpleMonteCarlo1(expiry,
                                      strike, 
							          spot, 
							          vol, 
							          rate, 
						              numberOfPaths);

	cout <<"the price is " << result << "\n";

    double tmp;
    cin >> tmp;

	return 0;
}
