/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#ifndef SIMPLEMC_H
#define SIMPLEMC_H

#include "payoff_2.h"

namespace derivs
{
    double simpleMonteCarlo2(
        const PayOff& thePayOff,
        double timeToExpiry,
        double spot,
        double vol,
        double rate,
        unsigned long numberOfPaths);
} // derivs

#endif
