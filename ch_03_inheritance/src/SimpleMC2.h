/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#ifndef SIMPLEMC2_H
#define SIMPLEMC2_H

#include "PayOff2.h"

double SimpleMonteCarlo2(const PayOff& thePayOff, 
                         double Expiry, 
						 double Spot,
						 double Vol, 
						 double r, 
						 unsigned long NumberOfPaths);

#endif
