#include "constant.hpp"
#include <cmath>

using namespace calc;

map<string,double> constants = 
{
    {"pi", M_PI},
    {"e",  M_E },
    {"fi", 1.618033988750}
};

Constant::Constant(string s)
{
    name = s;
}

Constant::~Constant() {}

void Constant::evaluate()
{   
    try
    {   
        stack.push(constants[name]);
    }
    catch(...)
    {
        clog << "no such constant: " + name;
    }
}