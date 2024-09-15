/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#include "simple_mc_2.h"
#include <iostream>
#include <memory>

int main()
{
    // Don't want to input every single value when I'm debugging
    double timeToExpiry = 0.5;
    double strike = 100.0;
    double spot = 95.0;
    double vol = 0.2;
    double rate = 0.05;
    unsigned long numberOfPaths = 500000;
    char cp = 'c';

    std::cout << "Default values..." << std::endl;
    std::cout << "timeToExpiry  : " << timeToExpiry << std::endl;
    std::cout << "strike        : " << strike << std::endl;
    std::cout << "spot          : " << spot << std::endl;
    std::cout << "vol           : " << vol << std::endl;
    std::cout << "rate          : " << rate << std::endl;
    std::cout << "numberOfPaths : " << numberOfPaths << std::endl;
    std::cout << "call/put [c/p]: " << cp << std::endl;

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
        std::cout << "call/put [c/p]: "; std::cin >> cp;
    }

    std::unique_ptr<const derivs::PayOff> thePayOffPtr;
    if (std::tolower(cp) == 'c')
        thePayOffPtr = std::make_unique<const derivs::PayOffCall>(strike);
    else
        thePayOffPtr = std::make_unique<const derivs::PayOffPut>(strike);

    const double result = derivs::simpleMonteCarlo2(
        *thePayOffPtr,
        timeToExpiry,
        spot,
        vol,
        rate,
        numberOfPaths);

    std::cout << "price: " << result << std::endl;
    double tmp;
    std::cin >> tmp;

    return 0;

}
