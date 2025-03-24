#include "piksel.hpp"
#include <cmath>
#include <stdexcpt.h>
#include <iostream>

using namespace std;

piksel::piksel(int a, int b)
{
    if(a < 0 || a >= max_x || b < 0 || b >= max_y )
    {
        throw invalid_argument("piksel nie moze byc poza ekranem");
    }
    x = a;
    y = b;
}

int piksel::gora()
{
    return y;
}

int piksel::dol()
{
    return max_y-y;
}

int piksel::lewa()
{
    return max_x-x;
}

int piksel::prawa()
{
    return x;
}

int odleglosc(const piksel &p, const piksel &q)
{
    return sqrt(pow(q.x - p.x, 2) + pow(q.y - p.y, 2));
}

int odleglosc(const piksel *p, const piksel *q)
{
    return sqrt(pow(q->x - p->x, 2) + pow(q->y - p->y, 2));
}

std::ostream& operator<<(std::ostream& out, piksel& a)
{
    string wyn = "";
    wyn += "(" + to_string(a.prawa()) + ", " + to_string(a.gora()) + ")"; 

    return out << wyn;
}