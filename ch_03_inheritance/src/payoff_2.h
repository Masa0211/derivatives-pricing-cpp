/*
*  Copyright (c) 2002 Mark Joshi
*  Copyright (c) 2024 Masahiro OHTA
*/

#ifndef PAYOFF2_H
#define PAYOFF2_H

namespace derivs
{
    class PayOff
    {
    public:

        PayOff() {};
        virtual double operator()(double spot) const = 0;
        virtual ~PayOff() {}

    private:

    };


    class PayOffCall final : public PayOff
    {
    public:

        PayOffCall(double strike);
        virtual double operator()(double spot) const override final;
        virtual ~PayOffCall() {}

    private:
        double strike_;
    };


    class PayOffPut final : public PayOff
    {
    public:

        PayOffPut(double strike_);
        virtual double operator()(double spot) const override final;
        virtual ~PayOffPut() {}

    private:
        double strike_;

    };
} // derivs

#endif
