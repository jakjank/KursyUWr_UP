#include "kolor.hpp"
#include <iostream>
#include <cmath>
#include <stdexcpt.h>

using namespace std;

kolor::kolor()
{
    R = 0;
    G = 0;
    B = 0;
}

kolor::kolor(int r, int g, int b)
{
    if(r > 255 or r < 0 or g > 255 or g < 0 or b > 255 or b < 0)
    {
        throw invalid_argument("argument spoza zakresu");
    }
    R = r;
    G = g;
    B = b;
}

void kolor::set_R(int x)
{
    if(x > 255 or x < 0)
    {
        throw invalid_argument("argument spoza zakresu");
    }
    R = x;
}
void kolor::set_G(int x)
{
    if(x > 255 or x < 0)
    {
        throw invalid_argument("argument spoza zakresu");
    }
    G = x;
}
void kolor::set_B(int x)
{
    if(x > 255 or x < 0)
    {
        throw invalid_argument("argument spoza zakresu");
    }
    B = x;
}
int kolor::get_R()
{
    return R;
}
int kolor::get_G()
{
    return G;
}
int kolor::get_B()
{
    return B;
}

void kolor::rozjasnij()
{
    set_R(min((int)(get_R() * 1.1), 255));
    set_G(min((int)(get_G() * 1.1), 255));
    set_B(min((int)(get_B() * 1.1), 255));
}

void kolor::pociemnij()
{
    set_R(round(get_R() * 0.9));
    set_G(round(get_G() * 0.9));
    set_B(round(get_B() * 0.9));
}

kolor kolor::srednia(kolor a, kolor b)
{
    return kolor((a.get_R() + b.get_R())/2, (a.get_G() + b.get_G())/2, (a.get_B() + b.get_B())/2);
}

std::ostream& operator<<(std::ostream& out, kolor& a)
{
    string wyn = "";
    wyn += "(" + to_string(a.R) + ", " + to_string(a.G) + ", " + to_string(a.B) + ")"; 

    return out << wyn;
}