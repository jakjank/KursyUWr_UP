#ifndef KOLORNAZWANY_HPP
#define KOLORNAZWANY_HPP
#include <iostream>
#include "kolor.hpp"

using namespace std; 

class kolornazwany : public virtual kolor
{
protected:
    string nazwa;
public:
    kolornazwany();
    kolornazwany(int r, int g, int b, string n);

    void set_name(string n);
    string get_name();
};

#endif