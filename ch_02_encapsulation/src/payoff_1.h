/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#ifndef PAYOFF_H
#define PAYOFF_H

class PayOff
{

public:
    enum class OptionType {CALL, PUT}; // use enum type instead of unscoped-enum
    PayOff(double Strike_, OptionType TheOptionsType_);
    double operator()(double Spot) const;

private:
    double strike_;
    OptionType theOptionsType_;

};

#endif
