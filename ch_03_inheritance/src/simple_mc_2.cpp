/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#include "simple_mc_2.h"
#include <cmath>
#include <random>

double derivs::simpleMonteCarlo2(
    const PayOff& thePayOff,
    const double timeToExpiry,
    const double spot,
    const double vol,
    const double rate,
    const unsigned long numberOfPaths)
{

    const double variance = vol * vol * timeToExpiry;
    const double rootVariance = std::sqrt(variance);
    const double itoCorrection = -0.5 * variance;
    const double rt = rate * timeToExpiry;
    const double df = std::exp(-rt);

    double movedSpot = spot * std::exp(itoCorrection) / df;
    double runningSum = 0.0;

    // set up random number
    constexpr std::size_t seed = 123456789;
    std::mt19937 generator(seed); // a specialization of std::mersenne_twister_engine
    std::normal_distribution<double> distribution(0.0, 1.0); // standard normal distribution

    for (auto i = 0u; i < numberOfPaths; ++i)
    {
        const double thisGaussian = distribution(generator);
        const double thisSpot = movedSpot * std::exp(rootVariance * thisGaussian);
        const double thisPayoff = thePayOff(thisSpot);
        runningSum += thisPayoff;
    }

    const double mean = runningSum / numberOfPaths;
    const double discountedMean = mean * df;
    return mean;
}
