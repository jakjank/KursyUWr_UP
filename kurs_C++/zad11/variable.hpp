#pragma once
#include "operand.hpp"

namespace calc
{
    int name_ok(string name);
    void set_var(string name, double val);

    class Variable : public Operand
    {
        string name;
    public:
        static map<string,double> variables;
        Variable(string name);
        ~Variable();
        void evaluate() override;
        friend void set_var(string name, double val);
        void clear_var();
    };
}