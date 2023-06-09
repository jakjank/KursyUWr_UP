#include "function.hpp"
#include <cmath>

using namespace calc;

map<std::string, Function::kind_of_f> Function::map_of_f = 
{
    {"+", f_add},
    {"-", f_sub},
    {"*", f_mul},
    {"/", f_div},
    {"%", f_modulo},
    {"min", f_min},
    {"max", f_max},
    {"log", f_log},
    {"pow", f_pow},
    {"abs", f_abs},
    {"sgn", f_sgn},
    {"floor", f_floor},
    {"ceil", f_ceil},
    {"frac", f_frac},
    {"sin", f_sin},
    {"cos", f_cos},
    {"atan", f_atan},
    {"acot", f_acot},
    {"ln", f_ln},
    {"exp", f_exp}
};

Function::Function(string s)
{
    name = map_of_f[s];
}

Function::~Function() {}

void Function::push(queue<Symbol*>& symbols)
{
    symbols.push(this);
}

void Function::evaluate()
{
    double a, b;

    switch (name)
    {
    case f_add :
        b = stack.top();
        stack.pop();
        a = stack.top();
        stack.pop();
        stack.push(a + b);
        break;
    case f_sub :
        b = stack.top();
        stack.pop();
        a = stack.top();
        stack.pop();
        stack.push(a - b);
        break;
    case f_mul :
        b = stack.top();
        stack.pop();
        a = stack.top();
        stack.pop();
        stack.push(a * b);
        break;
    case f_div :
        b = stack.top();
        stack.pop();
        a = stack.top();
        stack.pop();
        stack.push(a / b);
        break;
    case f_modulo :
        b = stack.top();
        stack.pop();
        a = stack.top();
        stack.pop();
        stack.push(fmod(a, b));
        break;
    case f_min :
        b = stack.top();
        stack.pop();
        a = stack.top();
        stack.pop();
        stack.push(min(a, b));
        break;
    case f_max :
        b = stack.top();
        stack.pop();
        a = stack.top();
        stack.pop();
        stack.push(max(a, b));
        break;
    case f_log :
        b = stack.top();
        stack.pop();
        a = stack.top();
        stack.pop();
        stack.push(log(a) / log(b));
        break;
    case f_pow :
        b = stack.top();
        stack.pop();
        a = stack.top();
        stack.pop();
        stack.push(pow(a, b));
        break;
    case f_abs :
        a =stack.top();
        stack.pop();
        stack.push(abs(a));
        break;
    case f_sgn :
        a = stack.top();
        stack.pop();
        if(a > 0)
        {
            stack.push(1);
        }
        else
        {
            if(a < 0)
            {
                stack.push(-1);
            }
            else
            {
                stack.push(0);
            }
        }
        break;
    case f_floor :
        a =stack.top();
        stack.pop();
        stack.push(floor(a));
        break;
    case f_ceil :
        a =stack.top();
        stack.pop();
        stack.push(ceil(a));
        break;
    case f_frac :
        a =stack.top();
        stack.pop();
        stack.push(a - floor(a));
        break;
    case f_sin :
        a =stack.top();
        stack.pop();
        stack.push(sin(a));
        break;
    case f_cos :
        a =stack.top();
        stack.pop();
        stack.push(cos(a));
        break;
    case f_atan :
        a =stack.top();
        stack.pop();
        stack.push(atan(a));
        break;
    case f_acot :
        a =stack.top();
        stack.pop();
        stack.push(atan(-a) + M_PI_2);
        break;
    case f_ln :
        a =stack.top();
        stack.pop();
        stack.push(log(a));
        break;
    case f_exp :
        a = stack.top();
        stack.pop();
        stack.push(exp(a));
        break;
    default:
        break;
    }
}