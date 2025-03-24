#pragma once
#include "symbol.hpp"

namespace calc
{
    class Operand : public Symbol
    {
        double value;
    public:
        Operand();
        ~Operand();
        void push(queue<Symbol*>& symbols);
        virtual void evaluate() override {cout << "operand";};
    };
}