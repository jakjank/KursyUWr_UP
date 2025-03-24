#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;

namespace obliczenia
{
    class wyjatek_wymierny     : public logic_error
    {
    public:
        wyjatek_wymierny(const string& s) 
        : logic_error(s){};
    };

    class przekroczenie_zakesu : public wyjatek_wymierny
    {
    public:
        przekroczenie_zakesu() 
        : wyjatek_wymierny("przekroczono zakres int"){};
    };

    class dzielenie_przez_0    : public wyjatek_wymierny
    {
    public:
        dzielenie_przez_0()    
        : wyjatek_wymierny("mianownik jest zerem"){};
    };

    class Wymierna
    {
    private:
        int licz, mian;

    public:
        Wymierna();
        Wymierna(int licz, int mian);
        Wymierna(int n);
        int licznik();
        int mianownik();
        void popraw();

        friend Wymierna operator-(Wymierna a);
        friend Wymierna operator!(Wymierna a);
        friend Wymierna operator+(const Wymierna& a, const Wymierna& b);
        friend Wymierna operator-(const Wymierna& a, const Wymierna& b);
        friend Wymierna operator*(const Wymierna& a, const Wymierna& b);
        friend Wymierna operator/(const Wymierna& a, const Wymierna& b);

        Wymierna& operator+=(const Wymierna& a);
        Wymierna& operator-=(const Wymierna& a);
        Wymierna& operator*=(const Wymierna& a);
        Wymierna& operator/=(const Wymierna& a);

        operator double();
        operator int();

        friend ostream& operator<<(ostream& output, const Wymierna& a);
    };
}