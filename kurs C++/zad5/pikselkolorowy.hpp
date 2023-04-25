#ifndef PIKSELKOLOROWY_HPP
#define PIKSELKOLOROWY_HPP
#include "piksel.hpp"
#include "kolortransparentny.hpp"

class pikselkolorowy : public piksel
{
protected:
    kolortransparentny kolor;
public:
    pikselkolorowy(int a, int b, kolortransparentny c);
    void przesun(int a, int b);
};


#endif