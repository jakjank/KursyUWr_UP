#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

class Plansza_mala
{
public:
    int pola[3][3];
    int tura;

    Plansza_mala();
    bool wykonaj_ruch(int wsp1, string wsp2);
    // typu bool zeby od razu sprawdzac czy udalo sie wykonac ruch
    bool wygrana();
};

class Plansza_duza
{
public:
    int pola[4][4];
    int tura;

    Plansza_duza();
    bool wykonaj_ruch(int wsp1, string wsp2);
    bool wygrana();
};