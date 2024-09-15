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
    PayOff(double strike_, OptionType optionsType_);
    double operator()(double spot) const;

private:
    double strike_;
    OptionType optionsType_;

};

#endif
