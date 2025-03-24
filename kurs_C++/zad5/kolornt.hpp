#ifndef KOLORNT_HPP
#define KOLORNT_HPP
#include "kolornazwany.hpp"
#include "kolortransparentny.hpp"
#include "kolor.hpp"

using namespace std;

class kolornt : public kolortransparentny, public kolornazwany
{

public:
    kolornt() = default;
    kolornt(int r, int g, int b, int d, string e);
};

#endif