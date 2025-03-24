#pragma once
#include "wyrazenia.hpp"

class Sin : public Operator1
{
public:
    Sin(Wyrazenie *argument);
    string zapis() override;
    double oblicz() override;
};

class Cos : public Operator1
{
public:
    Cos(Wyrazenie *argument);
    string zapis() override;
    double oblicz() override;
};

class Exp : public Operator1
{
public:
    Exp(Wyrazenie *argument);
    string zapis() override;
    double oblicz() override;
};

class Ln : public Operator1
{
public:
    Ln(Wyrazenie *argument);
    string zapis() override;
    double oblicz() override;
};

class Bezwzgl : public Operator1
{
public:
    Bezwzgl(Wyrazenie *argument);
    string zapis() override;
    double oblicz() override;
};

class Przeciw : public Operator1
{
public:
    Przeciw(Wyrazenie *argument);
    string zapis() override;
    double oblicz() override;
};

class Odwrot : public Operator1
{
public:
    Odwrot(Wyrazenie *argument);
    string zapis() override;
    double oblicz() override;
};