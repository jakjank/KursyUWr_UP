#ifndef PIKSEL_HPP
#define PIKSEL_HPP
#include <iostream>

class piksel
{
protected:
    static const int max_x = 1920;
    static const int max_y = 1080;
    int x;
    int y;

public:
    piksel(int a, int b);
    int gora();
    int dol();
    int lewa();
    int prawa();

    friend int odleglosc(const piksel &p, const piksel &q);
    friend int odleglosc(const piksel *p, const piksel *q);

    friend std::ostream& operator<<(std::ostream& out, piksel& A);
};

#endif
