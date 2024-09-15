/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#include "payoff_2.h"
#include <cmath>

derivs::PayOffCall::PayOffCall(const double strike)
    : strike_(strike)
{
}

double derivs::PayOffCall::operator() (const double spot) const
{
    return std::max(spot - strike_, 0.0);
}

derivs::PayOffPut::PayOffPut(const double strike)
    : strike_(strike)
{
}

double derivs::PayOffPut::operator()(const double spot) const
{
    return std::max(strike_ - spot, 0.0);
}
