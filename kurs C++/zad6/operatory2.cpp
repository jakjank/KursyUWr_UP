#include "operatory2.hpp"

dodaj::dodaj(Wyrazenie *argument, Wyrazenie *argument2) : Operator2(argument, argument2) {}
odejmij::odejmij(Wyrazenie *argument, Wyrazenie *argument2) : Operator2(argument, argument2) {}
mnoz::mnoz(Wyrazenie *argument, Wyrazenie *argument2) : Operator2(argument, argument2) {}
dziel::dziel(Wyrazenie *argument, Wyrazenie *argument2) : Operator2(argument, argument2) {}
logarytm::logarytm(Wyrazenie *argument, Wyrazenie *argument2) : Operator2(argument, argument2) {}
modulo::modulo(Wyrazenie *argument, Wyrazenie *argument2) : Operator2(argument, argument2) {}
potega::potega(Wyrazenie *argument, Wyrazenie *argument2) : Operator2(argument, argument2) {}

double dodaj::oblicz()
{
    return argument->oblicz() + argument2->oblicz();
}
double odejmij::oblicz()
{
    return argument->oblicz() - argument2->oblicz();
}
double mnoz::oblicz()
{
    return argument->oblicz() * argument2->oblicz();
}
double dziel::oblicz()
{
    return argument->oblicz() / argument2->oblicz();
}
double logarytm::oblicz()
{
    return log(argument2->oblicz()) / log(argument->oblicz());
}
double modulo::oblicz()
{
    return fmod(argument->oblicz(), argument2->oblicz());
}
double potega::oblicz()
{
    return pow(argument->oblicz(), argument2->oblicz());
}

bool dodaj::lewa()
{
    return true;
}
bool odejmij::lewa()
{
    return true;
}
bool mnoz::lewa()
{
    return true;
}
bool dziel::lewa()
{
    return true;
}
bool logarytm::lewa()
{
    return true;
}
bool modulo::lewa()
{
    return true;
}
bool potega::lewa()
{
    return false;
}

int dodaj::priorytet()
{
    return 6;
}
int odejmij::priorytet()
{
    return 6;
}
int mnoz::priorytet()
{
    return 5;
}
int dziel::priorytet()
{
    return 5;
}
int logarytm::priorytet()
{
    return 2;
}
int modulo::priorytet()
{
    return 4;
}
int potega::priorytet()
{
    return 3 ;
}

string nawiasy(int priorytet, Wyrazenie *argument)
{
    int priorytet_skladowej = argument->priorytet();

    if (priorytet > priorytet_skladowej) // mniejszy czyli wiekszy
    {
        return argument->zapis();
    }
    else if(priorytet < priorytet_skladowej)
    {
        return "(" + argument->zapis() + ")";
    }
    else if(!argument->lewa())
    {
        return argument->zapis();
    }
    return "(" + argument->zapis() + ")";
    
}

string dodaj::zapis()
{
    return nawiasy(this->priorytet(), argument) 
           + "+" + 
           nawiasy(this->priorytet(), argument2);
}
string odejmij::zapis()
{
    return nawiasy(this->priorytet(), argument) 
           + "-" + 
           nawiasy(this->priorytet(), argument2);
}
string mnoz::zapis()
{
    return nawiasy(this->priorytet(), argument) 
           + "*" + 
           nawiasy(this->priorytet(), argument2);
}
string dziel::zapis()
{
    return nawiasy(this->priorytet(), argument) 
           + "/" + 
           nawiasy(this->priorytet(), argument2);
}
string logarytm::zapis()
{
    return "log(" + 
           nawiasy(this->priorytet(), argument) 
           + ", " +
           nawiasy(this->priorytet(), argument2)
           + ")";
}
string modulo::zapis()
{
    return nawiasy(this->priorytet(), argument) 
           + "%" + 
           nawiasy(this->priorytet(), argument2);
}
string potega::zapis()
{
    return nawiasy(this->priorytet(), argument) 
           + "^" + 
           nawiasy(this->priorytet(), argument2);
}

