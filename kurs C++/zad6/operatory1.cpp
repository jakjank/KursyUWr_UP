#include "operatory1.hpp"

Sin::Sin(Wyrazenie *argument) : Operator1(argument){}
Cos::Cos(Wyrazenie *argument) : Operator1(argument) {}
Exp::Exp(Wyrazenie *argument) : Operator1(argument){}
Ln::Ln(Wyrazenie *argument) : Operator1(argument){}
Bezwzgl::Bezwzgl(Wyrazenie *argument) : Operator1(argument){}
Przeciw::Przeciw(Wyrazenie *argument) : Operator1(argument){}
Odwrot::Odwrot(Wyrazenie *argument) : Operator1(argument){}

string Sin::zapis()
{
    return "sin(" + argument->zapis() + ")";
}
string Cos::zapis()
{
    return "cos(" + argument->zapis() + ")";
}
string Exp::zapis()
{
    return "exp(" + argument->zapis() + ")";
}
string Ln::zapis()
{
    return "ln(" + argument->zapis() + ")";
}
string Bezwzgl::zapis()
{
    return "|" + argument->zapis() + "|";
}
string Przeciw::zapis()
{
    return "-(" + argument->zapis() + ")";
}
string Odwrot::zapis()
{
    return "1/(" + argument->zapis() + ")";
}

double Sin::oblicz()
{
    return sin(argument->oblicz());
}
double Cos::oblicz()
{
    return cos(argument->oblicz());
}
double Exp::oblicz()
{
    return exp(argument->oblicz());
}
double Ln::oblicz()
{
    return log(argument->oblicz());
}
double Bezwzgl::oblicz()
{
    return abs(argument->oblicz());
}
double Przeciw::oblicz()
{
    return (-1) * (argument->oblicz());
}
double Odwrot::oblicz()
{
    return 1 / (argument->oblicz());
}

