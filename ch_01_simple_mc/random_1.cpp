/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#include "random_1.h"
#include <cstdlib>
#include <cmath>

double getOneGaussianBySummation()
{
    double result=0;

    for (unsigned long j=0; j < 12; j++)
        result += std::rand()/static_cast<double>(RAND_MAX);

    result -= 6.0;

    return result;

}


double getOneGaussianByBoxMuller()
{
    double result;

    double x;
    double y;

    double sizeSquared;
    do
    {
        x = 2.0 * std::rand()/static_cast<double>(RAND_MAX)-1;
        y = 2.0 * std::rand()/static_cast<double>(RAND_MAX)-1;
        sizeSquared = x*x + y*y;
    }
    while
        ( sizeSquared >= 1.0);

    result = x * std::sqrt(-2.0 * std::log(sizeSquared) / sizeSquared);

    return result;

}
