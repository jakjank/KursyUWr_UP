#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

using namespace std;

class Wyrazenie
{
public:
    virtual double oblicz() = 0;
    virtual string zapis()  = 0;
    virtual int priorytet() {return 0;};
    virtual bool lewa() {return true;};
};

class Liczba: public Wyrazenie
{
    double wartosc;
public:
    Liczba(double w=0);
    string zapis();
    double oblicz();
};

class Zmienna: public Wyrazenie
{
private:
    static vector<pair<string, double>> zmienne;

public:
    string nazwa;
    Zmienna(string nazwa_zm);
    void dodaj_zmienna(double wartosc);
    void usun_zmienna ();
    void zmien_wartosc(double nowa_wartosc);
    string zapis();
    double oblicz();
};

class  Stala: public Wyrazenie
{
protected:
    double wartosc;
};

class Operator1: public Wyrazenie
{
public:
    Wyrazenie *argument;
    Operator1(Wyrazenie *argument);
};

class Operator2: public Operator1
{
public:
    Operator2(Wyrazenie *argument, Wyrazenie *argument2);
    Wyrazenie *argument2;
    // domyslnie zwracamy prioytet 1 i lewa=true
    // a zmieniamy jeszcze nizej
    virtual int priorytet() override {return 1;};
    virtual bool lewa() override {return true;};
};