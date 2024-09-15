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

    inline double cumNorm(const double x)
    {
        constexpr double ONE_OVER_SQRT_TWO = 7.07106781186547524e-1;
        return 0.5 * std::erfc(-x * ONE_OVER_SQRT_TWO);
    }

    inline double getBsPrice(
        const double timeToExpiry,
        const double strike,
        const double spot,
        const double vol,
        const double rate,
        const bool isCall = true)
    {
        const double sign = isCall ? 1.0 : -1.0;
        const double v = vol * vol * timeToExpiry;
        const double s = vol * std::sqrt(timeToExpiry);

        const double rt = rate * timeToExpiry;
        const double df = std::exp(-rt);
        if (s < DBL_EPSILON)
        {
            const double intrinsic = df * std::max(sign * (spot - strike), 0.0);
            return intrinsic;
        }

        const double lnM = std::log(spot / strike);
        const double d1 = (lnM + rt + 0.5 * v) / s;
        const double Nd1 = cumNorm(sign * d1);
        const double Nd2 = cumNorm(sign * (d1 - s));

        const double price = sign * (spot * Nd1 - df * strike * Nd2);

        return price;
    }

} // namespace

int main()
{
    // Don't want to input every single value when I'm debugging
    double timeToExpiry = 0.5;
    double strike = 100.0;
    double spot = 95.0;
    double vol = 0.2;
    double rate = 0.05;
    unsigned long numberOfPaths = 160000;

    std::cout << "Default values..." << std::endl;
    std::cout << "timeToExpiry  : " << timeToExpiry << std::endl;
    std::cout << "strike        : " << strike << std::endl;
    std::cout << "spot          : " << spot << std::endl;
    std::cout << "vol           : " << vol << std::endl;
    std::cout << "rate          : " << rate << std::endl;
    std::cout << "numberOfPaths : " << numberOfPaths << std::endl;

    std::cout << "Do you want to input values? [Y/N]: ";
    char yn; std::cin >> yn;
    if (std::tolower(yn) == 'y')
    {
        std::cout << "Enter values..." << std::endl;
        std::cout << "timeToExpiry  : "; std::cin >> timeToExpiry;
        std::cout << "strike        : "; std::cin >> strike;
        std::cout << "spot          : "; std::cin >> spot;
        std::cout << "vol           : "; std::cin >> vol;
        std::cout << "rate          : "; std::cin >> rate;
        std::cout << "numberOfPaths : "; std::cin >> numberOfPaths;
    }

    double result = simpleMonteCarlo1(
        timeToExpiry,
        strike,
        spot,
        vol,
        rate,
        numberOfPaths);

    std::cout <<"MC call price: " << result << std::endl;

    const double bsPrice = getBsPrice(timeToExpiry, strike, spot, vol, rate);
    std::cout <<"BS call price: " << bsPrice << std::endl;

    double tmp;
    std::cin >> tmp;

    return 0;
}
