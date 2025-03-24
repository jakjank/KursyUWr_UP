#pragma once
#include "wyrazenia.hpp"

class pi : public Stala
{
public:
    pi();
    string zapis() override;
    double oblicz();
};

class fi : public Stala
{
public:
    fi();
    string zapis() override;
    double oblicz();
};

class e : public Stala
{
public:
    e();
    string zapis() override;
    double oblicz();
};