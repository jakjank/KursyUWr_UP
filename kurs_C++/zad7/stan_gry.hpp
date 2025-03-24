#pragma once
#include <iostream>

using namespace std;

class Plansza
{
public:
    int rozmiar;
    int **pola;
    int tura;

    Plansza(int rozmiar);
    bool wykonaj_ruch(int w1, int w2);
    bool wygrana();
};