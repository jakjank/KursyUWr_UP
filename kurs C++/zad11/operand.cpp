#include "operand.hpp"

using namespace calc;

Operand::Operand() {}

Operand::~Operand() {}

void Operand::push(queue<Symbol*>& symbols)
{
    symbols.push(this);
}