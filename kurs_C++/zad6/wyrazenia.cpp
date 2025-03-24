#include "wyrazenia.hpp"

// Wszystkie definicje liczb i zmiennych
// oraz klasy operator1i operator2

vector<pair<string, double>> Zmienna::zmienne;

Operator1::Operator1(Wyrazenie *argument)
{
    this->argument = argument;
}
Operator2::Operator2(Wyrazenie *argument, Wyrazenie *argument2) : Operator1(argument)
{
    this->argument2 = argument2;
}
Liczba::Liczba(double wartosc)
{
    this->wartosc = wartosc;
}
string Liczba::zapis()
{
    string wynik = to_string(wartosc);
    int offset = 1;
    
    if (wynik.find_last_not_of('0') == wynik.find('.'))
    {
        offset = 0;
    }
    wynik.erase(wynik.find_last_not_of('0') + offset, string::npos);

    return wynik;
}
double Liczba::oblicz()
{
    return wartosc;
}

Zmienna::Zmienna(string nazwa_zm)
{
    this->nazwa = nazwa_zm;
}

void Zmienna::dodaj_zmienna(double wartosc)
{   
    try
    {
        for(int i=0; i<zmienne.size(); i++)
        {
            if(zmienne[i].first == nazwa)
            {
                throw invalid_argument("");
            }
        }
    }
    catch(invalid_argument)
    {
        cout<< "zmiennna " << nazwa << " juz istnieje" << '\n';
    }
    zmienne.push_back(make_pair(nazwa, wartosc));
}

void Zmienna::usun_zmienna()
{
    try
    {
        for(int i=0; i<zmienne.size(); i++)
        {
            if(zmienne[i].first == nazwa)
            {
                zmienne.erase(zmienne.begin() + i);
                return;
            }
        }
        throw invalid_argument("");
    }
    catch(invalid_argument)
    {
        cout << "Zmienna " << nazwa << " nie istniala" << '\n';
    }
}

void Zmienna::zmien_wartosc(double nowa_wartosc)
{
    try
    {
        for(int i=0; i<zmienne.size(); i++)
        {
            if(zmienne[i].first == nazwa)
            {
                zmienne[i].second = nowa_wartosc;
                return;
            }
        }
        throw invalid_argument("");
    }
    catch(invalid_argument)
    {
        cout << "Zmienna " << nazwa << " nie istnieje" << '\n';
    }
}

string Zmienna::zapis()
{
    return nazwa;
}

double Zmienna::oblicz()
{
    for(int i=0; i<zmienne.size(); i++)
    {
        if(zmienne[i].first == nazwa)
        {
            return zmienne[i].second;
        }
    }
    return 0; 
}
