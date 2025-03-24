#include "pikselkolorowy.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

pikselkolorowy::pikselkolorowy(int a, int b, kolortransparentny c):piksel(a,b)
{
    kolor = c;
}

void pikselkolorowy::przesun(int a, int b)
{
    if(x + a >= max_x || x + a < 0 || y + b >= max_y || y + b < 0)
    {
        throw invalid_argument("piksel poza ekranem");
    }
    x+=a;
    y+=b;
}