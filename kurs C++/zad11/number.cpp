#include "number.hpp"

using namespace calc;

Number::Number(double val)
{
    value = val;
}

Number::~Number(){}

void Number::evaluate()
{
    stack.push(value);
}