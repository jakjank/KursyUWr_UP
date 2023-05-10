#include "wymierna.hpp"

namespace obliczenia
{
int NWD(int a, int b)
{
    while(a!=b)
        if(a>b)
            a-=b; //lub a = a - b;
        else
            b-=a; //lub b = b-a
    return a; // lub b - obie zmienne przechowują wynik NWD(a,b)
}

void Wymierna::popraw()
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

Wymierna::Wymierna()
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

Wymierna::Wymierna(int n)
{
    licz = n;
    mian = 1;
}

int Wymierna::licznik()
{
    return licz;
}

int Wymierna::mianownik()
{
    return mian;
}

Wymierna operator-(Wymierna a)
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

Wymierna::operator double()
{
    return (double) licz/mian;
}

Wymierna::operator int()
{
    return licz/mian;
}

ostream &operator<<(ostream &output, const Wymierna &a)
{
    output << a.licz / a.mian;
    int reszta = a.licz % a.mian;
    //cout<<"reszta "<<reszta<<endl;
    int k = 0;
    int bylo[10];
    int cyfra;
    bool okres = false;

    while(reszta != 0 && !okres)
    {
        //cout<<"reszta: "<<reszta<<endl;
        cyfra = 10*reszta / a.mian;
        //cout<<"cyfra: "<<cyfra<<endl;
        bylo[k] = cyfra;
        for(int i=0; i<k; i++)
        {
            if(bylo[i] == cyfra)
            {
                okres = true;
            }
        }
        reszta = 10*reszta % a.mian;
        k += 1;
    }

    if(k>0) output << ".";
    for(int i=0;i<k;i++)
    {
        if(okres)
        {
            if(bylo[i] == bylo[k-1] && i != k-1) output<<"(";
            if(i == k-1)
            {
                output<<")";
                break;
            }
            else
            {
                output<<bylo[i];
            }
        }
        else
        {
            output << bylo[i];
        }
    }
    return output;
}

}