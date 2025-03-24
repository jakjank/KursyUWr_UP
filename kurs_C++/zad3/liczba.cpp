#include "liczba.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

//KONSTRUKTORY------------------------------

liczba::liczba(double x)
{
    aktualna_wartosc = x;
    historia = new double[rozmiar_maks];
    if( x != 0) // zeby nie było powtorzen w historii
    {
        rozmiar_akt = 1;
        historia[0] = 0; //zakładamy, że każda liczba pierwotnie była zerem
    }
    else
    {
        rozmiar_akt = 0;
    }
}

liczba::liczba() : liczba(0) {}

liczba::liczba(const liczba &liczba2)
{
    rozmiar_akt = liczba2.rozmiar_akt;
    rozmiar_maks = liczba2.rozmiar_maks;
    aktualna_wartosc = liczba2.aktualna_wartosc;
    historia = new double[rozmiar_maks];

    for(int i = 0; i < rozmiar_akt; i++)
    {
        historia[i] = liczba2.historia[i];
    }
}

liczba::liczba(liczba &&liczba2) 
    : aktualna_wartosc(0), historia(nullptr)
{
    swap(aktualna_wartosc, liczba2.aktualna_wartosc);
    swap(historia, liczba2.historia);
}

liczba::~liczba()
{
    if(historia != nullptr)
    {
        delete[] historia;
    }
}

liczba & liczba::operator=(const liczba &liczba2)
{
    if(this == &liczba2) throw invalid_argument ("nie mozna przypisac liczby jako siebie sama");
    
    delete[] historia;
    aktualna_wartosc = liczba2.aktualna_wartosc;
    memcpy(historia , liczba2.historia , liczba2.rozmiar_akt);
    return *this;
}

liczba & liczba::operator=(liczba &&liczba2)
{
    if(this == &liczba2) throw invalid_argument ("nie mozna przypisac liczby jako siebie sama");
    
    delete[] historia;
    aktualna_wartosc = liczba2.aktualna_wartosc;
    memcpy(historia , liczba2.historia , liczba2.rozmiar_akt);
    liczba2.~liczba();

    return *this;
}

//FUNKCJE-----------------------------------

double liczba::zwroc(int indeks)
{
    if(indeks >= rozmiar_akt || indeks < 0) 
        throw invalid_argument("pozycja spoza zakresu");
    
    return historia[indeks];
}

void liczba::ustaw(double nowa_wart)
{
    if(rozmiar_akt < rozmiar_maks)
    {
        historia[rozmiar_akt] = aktualna_wartosc;
        aktualna_wartosc = nowa_wart;
        rozmiar_akt++;
    }
    else
    {
        for(int i = 0; i < rozmiar_maks-1; i++)
        {
            historia[i] = this->zwroc(i+1);
        }
        historia[rozmiar_maks-1] = aktualna_wartosc;
        aktualna_wartosc = nowa_wart;
        
    }
}

void liczba::przywroc(int indeks)
{
    if(indeks >= rozmiar_akt || indeks < 0) 
        throw invalid_argument("indeks spoza zakresu");
    ustaw(historia[indeks]);
}

double liczba::wartosc()
{
    return aktualna_wartosc;
}


//COUT--------------------------------------

std::ostream& operator<<(std::ostream& out, const liczba& x)
{
    return out << x.aktualna_wartosc;
}