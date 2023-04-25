#ifndef KOLORTRANSPARENTNY_HPP
#define KOLORTRANSPARENTNY_HPP
#include "kolor.hpp"

class kolortransparentny : public virtual kolor
{

protected:
    unsigned char alfa;
public:
    kolortransparentny();
    kolortransparentny(int r, int g, int b, int alfa);

    void set_alfa(int a);
    int get_alfa();
};


#endif