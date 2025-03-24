#ifndef TROJKAT_HPP
#define TROJKAT_HPP

#include "punkt.hpp"
#include "wektor.hpp"
#include "prosta.hpp"

using namespace std;

class trojkat
{
    punkt a , b , c;

public:
    trojkat(punkt w1, punkt w2, punkt w3);

    void przesun(wektor w);

    void obrot(punkt p , double alfa);

    void symetria(punkt p);

    void symetria_x();

    void symetria_y();

    double obwod();

    double pole();

    bool czy_wew(punkt p);

    punkt w_a();
    punkt w_b();
    punkt w_c();
};

ostream & operator<< (ostream &os, trojkat t);

#endif