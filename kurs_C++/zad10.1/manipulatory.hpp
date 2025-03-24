#pragma once
#include <iostream>
#include <istream>

using namespace std;

istream& clearline(istream& istr);

struct ignore
{
    int how_many;
    ignore(int h);
    friend istream& operator>>(istream& istr, const ignore &ign);
};

ostream& coma(ostream& ostr);

ostream& colon(ostream& ostr);

struct index
{
    int number;
    int width;
    index(int n, int w);
    friend ostream& operator<<(ostream& ostr, const index &ind);
};