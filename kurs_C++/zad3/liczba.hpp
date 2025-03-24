#ifndef LICZBA_HPP
#define LICZBA_HPP

#include <iostream>

class liczba{

private:
    int rozmiar_maks = 3;
    int rozmiar_akt;
    double aktualna_wartosc;
    double *historia = nullptr;

public:
    liczba();
    liczba(double x);
    liczba(const liczba &liczba2);
    liczba(liczba &&liczba2);
    ~liczba();

    liczba& operator=(const liczba &liczba2);
    liczba& operator=(liczba &&liczba2);

    void ustaw(double n);
    double zwroc(int indeks);
    void przywroc(int indeks);
    double wartosc();
    int zwroc_rozmiar_historii(); //tylko do sprawdzania konstr. przenoszacego

    friend std::ostream& operator<<(std::ostream& out, const liczba& x);
};

#endif