#pragma once
#include "operand.hpp"

using namespace std;

namespace calc
{
    class Constant : public Operand
    {
        string name;
        map<string, double> constants;
    public:
        Constant(string s);
        ~Constant();
        void evaluate() override;
    };
}