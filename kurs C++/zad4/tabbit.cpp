#include <iostream>
#include <cmath>
#include "tabbit.hpp"


using namespace std;

const int tab_bit::rozmiarSlowa = 64;

tab_bit::tab_bit(int rozmiar) //konstruktor wypelniajacy zerami
{
    int ile_slow;
    dl       = rozmiar;
    ile_slow = ceil(rozmiar / rozmiarSlowa);
    tab      = new slowo[ile_slow];

    for(int i = 0; i < ile_slow; i++)
    {
        tab[i] = 0;
    }
}

tab_bit::tab_bit(slowo tb) //konstrukto ze wzorcem
{
    dl     = rozmiarSlowa;
    tab    = new slowo[1];
    tab[0] = 0;
}

tab_bit::tab_bit(const tab_bit& tb) //konstruktor kopiujący
{
    int ile_slow;
    ile_slow = ceil(tb.dl / rozmiarSlowa);
    tab      = new slowo[ile_slow];

    for (int i = 0; i < ile_slow; i++)
    {
        tab[i] = tb.tab[i];
    }
}

tab_bit::tab_bit(tab_bit&& tb) // konstruktor przenoszący
{
    dl = tb.dl;
    tab = tb.tab;
    tb.tab = nullptr;
}

tab_bit& tab_bit::operator=(const tab_bit& tb) // operator przypisania kopiującego
{
    if (this == &tb) // zapobiega samokopiowaniu
        return *this;

    int ile_slow;
    delete[] tab;
    dl       = tb.dl;
    ile_slow = (int) ceil (tb.dl / rozmiarSlowa);
    tab      = new slowo[ile_slow];

    for (int i = 0; i < ile_slow; i++)
    {
        tab[i] = tb.tab[i]; 
    }

    return *this;
}

tab_bit& tab_bit::operator=(tab_bit&& tb) // operator przypisania przenoszącego
{
    if (this == &tb)
        return *this;
    
    delete[] tab; 
    dl     = tb.dl;
    tab    = tb.tab; 
    tb.tab = nullptr;

    return *this;
}

tab_bit::~tab_bit()
{
    if(tab != nullptr)
        delete[] tab;
}

