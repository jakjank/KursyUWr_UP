#include "stale.hpp"

pi::pi(){}
fi::fi(){}
e::e(){}

string pi::zapis()
{
    return "pi";
}

string fi::zapis()
{
    return "fi";
}

string e::zapis()
{
    return "e";
}

double pi::oblicz()
{
    return M_1_PI;
}

double fi::oblicz()
{
    return 1,6180339887;
}

double e::oblicz()
{
    return M_E;
}