#pragma once
#include "operand.hpp"

namespace calc
{
    class Number : public Operand
    {
        double value;
    public:
        Number(double val);
        ~Number();
        void evaluate() override;
    };
}