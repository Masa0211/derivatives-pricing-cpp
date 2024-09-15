/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#include "simple_mc.h"
#include <iostream>

int main()
{
    // Don't want to input every single value when I'm debugging
    double timeToExpiry = 0.5;
    double strike = 100.0;
    double spot = 95.0;
    double vol = 0.2;
    double rate = 0.05;
    unsigned long numberOfPaths = 500000;

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

    const PayOff callPayOff(strike, PayOff::call);
    const PayOff putPayOff(strike, PayOff::put);

    double resultCall = simpleMonteCarlo2(
        callPayOff,
        timeToExpiry,
        spot,
        vol,
        rate,
        numberOfPaths);

    double resultPut = simpleMonteCarlo2(
        putPayOff,
        timeToExpiry,
        spot,
        vol,
        rate,
        numberOfPaths);

    std::cout << "call price: " << resultCall << std::endl;
    std::cout << "put  price: " << resultPut << std::endl;

    double tmp;
    std::cin >> tmp;

    return 0;

}
