#include <vector>
#include "wymierna.hpp"

using namespace std;

namespace obliczenia
{
int NWD(int a, int b) noexcept
{
    while(a!=b)
        if(a>b)
            a-=b; //lub a = a - b;
        else
            b-=a; //lub b = b-a
    return a; // lub b - obie zmienne przechowują wynik NWD(a,b)
}

void Wymierna::popraw() noexcept
{
    if(licz==0) return;
    int nwd = NWD(abs(licz), abs(mian));
    licz = licz/nwd;
    mian = mian/nwd;

    if(mian < 0)
    {
        licz *= -1;
        mian *= -1;
    }
}

Wymierna::Wymierna() noexcept
{
    licz = 0;
    mian = 1;
}

Wymierna::Wymierna(int a, int b)
{
    if(b == 0) throw dzielenie_przez_0();

    licz = a;
    mian = b;
    popraw();
}

Wymierna::Wymierna(int n) noexcept
{
    licz = n;
    mian = 1;
}

int Wymierna::licznik() noexcept
{
    return licz;
}

int Wymierna::mianownik() noexcept
{
    return mian;
}

Wymierna operator-(Wymierna a) //moze rzucic, bo int e (-x-1,x)
{
    int licznik   = a.licznik() * -1;
    int mianownik = a.mianownik();

    return Wymierna(licznik, mianownik); //poprawia w konstruktorze
}

Wymierna operator!(Wymierna a)
{
    int licznik   = a.mianownik();
    int mianownik = a.licznik();

    return Wymierna(licznik,mianownik);
}

Wymierna operator+(const Wymierna &a, const Wymierna &b)
{
    long long licznik   = a.licz*b.mian + b.licz*a.mian;
    long long mianownik = a.mian*b.mian;
    if(licznik > INT_MAX || licznik < INT_MIN || mianownik > INT_MAX || mianownik < INT_MIN)
        throw przekroczenie_zakesu();

    return Wymierna((int)licznik, (int)mianownik);
}

Wymierna operator-(const Wymierna &a, const Wymierna &b)
{
    long long licznik   = a.licz*b.mian - b.licz*a.mian;
    long long mianownik = a.mian*b.mian;
    if(licznik > INT_MAX || licznik < INT_MIN || mianownik > INT_MAX || mianownik < INT_MIN)
        throw przekroczenie_zakesu();

    return Wymierna((int)licznik, (int)mianownik); 
}

Wymierna operator*(const Wymierna &a, const Wymierna &b)
{
    long long licznik   = a.licz*b.licz;
    long long mianownik = a.mian*b.mian;
    if(licznik > INT_MAX || licznik < INT_MIN || mianownik > INT_MAX || mianownik < INT_MIN)
        throw przekroczenie_zakesu();

    return Wymierna((int)licznik, (int)mianownik);
}

Wymierna operator/(const Wymierna &a, const Wymierna &b)
{
    long long licznik   = a.licz*b.mian;
    long long mianownik = a.mian*b.licz;
    if(licznik > INT_MAX || licznik < INT_MIN || mianownik > INT_MAX || mianownik < INT_MIN)
        throw przekroczenie_zakesu();

    return Wymierna((int)licznik, (int)mianownik);
}

Wymierna &Wymierna::operator+=(const Wymierna &a)
{
    long long licznik   = licz*a.mian + mian*a.licz;
    long long mianownik = mian*a.mian;
    if(licznik > INT_MAX || licznik < INT_MIN || mianownik > INT_MAX || mianownik < INT_MIN)
        throw przekroczenie_zakesu();

    licz  = licz*a.mian + mian*a.licz;
    mian *= a.mian;
    popraw();
    return *this;
}

Wymierna &Wymierna::operator-=(const Wymierna &a)
{
    long long licznik   = licz*a.mian - mian*a.licz;
    long long mianownik = mian*a.mian;
    if(licznik > INT_MAX || licznik < INT_MIN || mianownik > INT_MAX || mianownik < INT_MIN)
        throw przekroczenie_zakesu();

    licz  = licz*a.mian - mian*a.licz;
    mian *= a.mian;
    popraw();
    return *this;
}

Wymierna &Wymierna::operator*=(const Wymierna &a)
{
    long long licznik   = licz*a.licz;
    long long mianownik = mian*a.mian;
    if(licznik > INT_MAX || licznik < INT_MIN || mianownik > INT_MAX || mianownik < INT_MIN)
        throw przekroczenie_zakesu();

    licz  = licz*a.licz;
    mian *= a.mian;
    popraw();
    return *this;
}

Wymierna &Wymierna::operator/=(const Wymierna &a)
{
    long long licznik   = licz*a.mian;
    long long mianownik = mian*a.licz;
    if(licznik > INT_MAX || licznik < INT_MIN || mianownik > INT_MAX || mianownik < INT_MIN)
        throw przekroczenie_zakesu();

    licz  = licz*a.mian;
    mian *= a.licz;
    popraw();
    return *this;
}

Wymierna::operator double() noexcept
{
    return (double) licz/mian;
}

Wymierna::operator int() noexcept
{
    return licz/mian;
}

ostream &operator<<(ostream &output, const Wymierna &a) noexcept
    {
        std::vector <int> reszty;
        std::vector <int> wynik;

        unsigned int i, j;
        int reszta;

        reszta = a.licz % a.mian;
        if (reszta == 0)
        {
            if(a.licz / a.mian < 0)
            {
                output << "-" << a.licz / a.mian;
            }
            else
            {
                output << a.licz / a.mian;
            }
            return output;
        }

        if(a.licz * a.mian < 0)
        {
            output << "-";
        }

        if (reszta < 0)
        {
            reszta *= (-1);
        }

        reszty.push_back (reszta);
        
        output << a.licz / a.mian;

        while(true)
        {
            wynik.push_back (reszta * 10 / a.mian);
            reszta = reszta * 10 % a.mian;
            
            if (reszta == 0)
            {
                output << ".";
                for (i = 0; i < wynik.size(); i++)
                    output << wynik[i];
                return output;
            }

            for (j = 0; j < reszty.size(); j++)
            {
                if (reszta == reszty[j])
                {
                    output << ".";
                    for (i = 0; i < j; i++)
                        output << wynik[i];

                    output << "(";
                    for (i = j; i < wynik.size(); i++)
                        output << wynik[i];
                    output << ")";

                    return output;
                }
            }
            reszty.push_back (reszta);
        }
    } 
}
