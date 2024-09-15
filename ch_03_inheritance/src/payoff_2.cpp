/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#include "payoff_2.h"
#include "minmax.h"

PayOffCall::PayOffCall(double Strike_) : Strike(Strike_)
{
}

double PayOffCall::operator () (double Spot) const
{
    return max(Spot-Strike,0.0);
}


double PayOffPut::operator () (double Spot) const
{
    return max(Strike-Spot,0.0);
}

PayOffPut::PayOffPut(double Strike_) : Strike(Strike_)
{
}
