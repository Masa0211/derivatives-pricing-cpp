/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#include "payoff_1.h"
#include <cmath>

PayOff::PayOff(double Strike_, OptionType TheOptionsType_)
:
    Strike(Strike_), TheOptionsType(TheOptionsType_)
{
}

double PayOff::operator ()(double spot) const
{
    switch (TheOptionsType)
    {
    case call : 
        return std::max(spot-Strike,0.0);

    case put:
        return std::max(Strike-spot,0.0);

    default: 
        throw("unknown option type found.");

    }
}
