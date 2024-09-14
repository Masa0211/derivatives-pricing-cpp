/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#include "random_1.h"
#include <iostream>
#include <cmath>

namespace
{
    double simpleMonteCarlo1(double timeToExpiry,
        double strike,
        double spot,
        double vol,
        double rate,
        unsigned long numberOfPaths)
    {

        double variance = vol * vol * timeToExpiry;
        double rootVariance = std::sqrt(variance);
        double itoCorrection = -0.5 * variance;

        double movedSpot = spot * std::exp(rate * timeToExpiry + itoCorrection);
        double thisSpot;
        double runningSum = 0;

        for (unsigned long i = 0; i < numberOfPaths; i++)
        {
            double thisGaussian = getOneGaussianByBoxMuller();
            thisSpot = movedSpot * std::exp(rootVariance * thisGaussian);
            double thisPayoff = thisSpot - strike;
            thisPayoff = thisPayoff > 0 ? thisPayoff : 0;
            runningSum += thisPayoff;
        }

        double mean = runningSum / numberOfPaths;
        mean *= std::exp(-rate * timeToExpiry);
        return mean;
    }

    template <typename T>
    void inputValue(T& value, const std::string& msg)
    {
        std::cout << msg << ": ";
        std::cin >> value;
        // std::cout << "\n";
        return;
    }
} // namespace

int main()
{
    double timeToExpiry;
    double strike; 
    double spot; 
    double vol; 
    double rate;
    unsigned long numberOfPaths;

    inputValue(timeToExpiry, "Enter timeToExpiry");
    inputValue(strike, "Enter strike");
    inputValue(spot, "Enter spot");
    inputValue(vol, "Enter vol");
    inputValue(rate, "Enter rate");
    inputValue(numberOfPaths, "Enter number of paths");

    double result = simpleMonteCarlo1(timeToExpiry,
                                      strike, 
                                      spot, 
                                      vol, 
                                      rate, 
                                      numberOfPaths);

    std::cout <<"the price is " << result << std::endl;

    double tmp;
    std::cin >> tmp;

    return 0;
}
