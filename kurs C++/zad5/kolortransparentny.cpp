#include "kolortransparentny.hpp"
#include <iostream>
#include <stdexcpt.h>

using namespace std;

kolortransparentny::kolortransparentny():kolor()
{
    alfa  = 255;
}
kolortransparentny::kolortransparentny(int r, int g, int b, int a):kolor(r,g,b)
{
    if(r > 255 or r < 0 or g > 255 or g < 0 or b > 255 or b < 0 or a > 255 or a < 0)
    {
        throw invalid_argument("argument spoza zakresu");
    }
    alfa  = a;
}

void kolortransparentny::set_alfa(int a)
{
    if(a > 255 or a < 0)
    {
        throw invalid_argument("argument spoza zakresu");
    }
    alfa = a;
}
int kolortransparentny::get_alfa()
{
    return alfa;
}