#include "variable.hpp"

using namespace calc;

map<string,double> Variable::variables;

string forbidden_var_names[] = {"+", "-", "*", "/", "^", "%",
                                "min", "max", "log", "print",
                                "set", "to", "clear", "exit",
                                "abs", "sgn", "floor","ceil",
                                "frac","sin", "cos",  "atan",
                                "acot", "ln", "exp","pi","e",
                                "fi"};

Variable::Variable(string s)
{
    name = s;
}

Variable::~Variable() {}

int calc::name_ok(string name)
{
    for(int i=0; i<forbidden_var_names->size(); i++)
    {
        if(name == forbidden_var_names[i]) return 0;
    }
    return 1;
}

void calc::set_var(string name, double val)
{
    if(name_ok(name) == 0) throw invalid_argument("Wrong name of variable: " + name);
    Variable::variables.insert_or_assign(name, val);
}

void Variable::evaluate()
{
    if(variables.count(name))
    {
        stack.push(variables[name]);
    }
    else
    {
        throw invalid_argument("no such variable: " + name);
    }
}

void Variable::clear_var()
{
    Variable::variables.clear();
}
