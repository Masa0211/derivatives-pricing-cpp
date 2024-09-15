/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#include "payoff_1.h"
#include <cmath>

PayOff::PayOff(const double strike, const OptionType optionsType)
    : strike_(strike)
    , optionsType_(optionsType)
{
    // validate the type in the constructor
    if (optionsType_ != OptionType::CALL && optionsType_ != OptionType::PUT)
    {
        throw("unknown option type found.");
    }
}

double PayOff::operator()(const double spot) const
{
    switch (optionsType_)
    {
    case OptionType::CALL:
        return std::max(spot - strike_, 0.0);

    case OptionType::PUT:
        return std::max(strike_ - spot, 0.0);

    default:
        throw("unknown option type found.");

    }
}
