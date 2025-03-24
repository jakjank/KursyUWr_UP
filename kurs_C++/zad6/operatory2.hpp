#pragma once
#include "wyrazenia.hpp"

class dodaj: public Operator2
{
public:
    dodaj(Wyrazenie *argument, Wyrazenie *argument2);
    string zapis() override;
    double oblicz() override;
    int priorytet() override;
    bool lewa() override;
};

class odejmij: public Operator2
{
public:
    odejmij(Wyrazenie *argument, Wyrazenie *argument2);
    string zapis() override;
    double oblicz() override;
    int priorytet() override;
    bool lewa() override;
};

class mnoz: public Operator2
{
public:
    mnoz(Wyrazenie *argument, Wyrazenie *argument2);
    string zapis() override;
    double oblicz() override;
    int priorytet() override;
    bool lewa() override;
};

class dziel: public Operator2
{
public:
    dziel(Wyrazenie *argument, Wyrazenie *argument2);
    string zapis() override;
    double oblicz() override;
    int priorytet() override;
    bool lewa() override;
};

class logarytm: public Operator2
{
public:
    logarytm(Wyrazenie *argument, Wyrazenie *argument2);
    string zapis() override;
    double oblicz() override;
    int priorytet() override;
    bool lewa() override;
};

class modulo: public Operator2
{
public:
    modulo(Wyrazenie *argument, Wyrazenie *argument2);
    string zapis() override;
    double oblicz() override;
    int priorytet() override;
    bool lewa() override;
};

class potega: public Operator2
{
public:
    potega(Wyrazenie *argument, Wyrazenie *argument2);
    string zapis() override;
    double oblicz() override;
    int priorytet() override;
    bool lewa() override;
};