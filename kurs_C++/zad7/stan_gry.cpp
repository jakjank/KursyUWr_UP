#include "stan_gry.hpp"

using namespace std;

Plansza::Plansza(int n)
{
    pola = new int*[n];
    for(int i=0; i<n; i++)
    {
        pola[i] = new int[n];
    }
    rozmiar = n;
    tura = 0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            pola[i][j] = 0;
        }
    }

}

bool Plansza::wykonaj_ruch(int w1, int w2)
{
    if(w1<0 || w1>rozmiar-1 || w2<0 || w2>rozmiar-1)
    {
        cout << "Wprowadzono zle dane"<<endl;
        return false;
    }
    if(pola[w1][w2] != 0)
    {
        cout << "Wybrane pole jest juz zajete"<<endl;
        return false;
    }
    if(tura % 2 == 0)
    {
        pola[w1][w2] = 1;
    }
    else
    {
        pola[w1][w2] = -1;
    }
    tura++;
    return true;
}

bool Plansza::wygrana()
{
    int suma;
    for(int i=0; i<rozmiar; i++)
    {
        suma = 0;
        for(int j=0; j<rozmiar; j++)
        {
            suma += pola[i][j];
        }
        if(suma == rozmiar || suma == -rozmiar) return true;
    }
    for(int i=0; i<rozmiar; i++)
    {
        suma = 0;
        for(int j=0; j<rozmiar; j++)
        {
            suma += pola[j][i];
        }
        if(suma == rozmiar || suma == -rozmiar) return true;
    }
    suma = 0;
    for(int i=0; i<rozmiar; i++)
    {
        suma += pola[rozmiar-i-1][i];
    }
    if(suma == rozmiar || suma == -rozmiar) return true;
    suma = 0;
    for(int i=0; i<rozmiar; i++)
    {
        suma += pola[i][i];
    }
    if(suma == rozmiar || suma == -rozmiar) return true;
    return false;
}