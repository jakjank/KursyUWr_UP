#ifndef F_GLOB_HPP
#define F_GLOB_HPP

#include "punkt.hpp"
#include "odcinek.hpp"
#include "wektor.hpp"
#include "prosta.hpp"
#include "trojkat.hpp"

double odleglosc (punkt a , punkt b);

bool czy_rownolegle(odcinek a , odcinek b);

bool czy_prostopadle(odcinek a , odcinek b);

double min(double x , double y);

double max(double x , double y);

bool rozlacznosc(trojkat t1 , trojkat t2);

bool zawieranie(trojkat t1 , trojkat t2);

#endif