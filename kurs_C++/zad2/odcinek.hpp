#ifndef ODCINEK_HPP
#define ODCINEK_HPP

#include "punkt.hpp"
#include "wektor.hpp"
#include "prosta.hpp"

using namespace std;

class odcinek
{
    punkt poczatek , koniec;

public:
    odcinek (punkt a , punkt b);

    void przesun (wektor w);

    void obrot (punkt p , double alfa);

    void symetria(punkt p);

    void symetria_x();

    void symetria_y();

    double dlugosc();

    bool czy_nalezy(punkt p);

    punkt wsp_pocz();

    punkt wsp_kon();
};

ostream & operator<< (ostream &os, odcinek l);

#endif