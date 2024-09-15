/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#ifndef SIMPLEMC_H
#define SIMPLEMC_H

#include "PayOff1.h"

double SimpleMonteCarlo2(const PayOff& thePayOff, 
                         double Expiry, 
						 double Spot,
						 double Vol, 
						 double r, 
						 unsigned long NumberOfPaths);


#endif
