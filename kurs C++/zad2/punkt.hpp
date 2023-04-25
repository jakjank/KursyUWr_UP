#ifndef PUNKT_HPP
#define PUNKT_HPP

#include <iostream>
#include "prosta.hpp"
#include "wektor.hpp"

class punkt
{
private:
    double x , y;

public:
    punkt ();

    punkt (double a , double b);

    double wsp_x ();

    double wsp_y ();

    void przesun (wektor w);

    void obrot (punkt p , double kat);

    void symetria (punkt p);

    void symetria_x();

    void symetria_y();
};

ostream & operator<< (ostream &os, punkt p);

#endif