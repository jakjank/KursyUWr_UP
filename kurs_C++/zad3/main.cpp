#include "liczba.hpp"
#include <iostream>

using namespace std;

int main()
{
    liczba a = liczba(); // sprawdzamy konstruktory bezparametrowy i z wart. poczatkowa
    cout << a << endl;
    
    a.ustaw(1);
    a.ustaw(2);
    a.ustaw(3);

    cout << "sprawdzamy czy poprzednie wartosci sie zachowaly" << endl
         << "(od najwczesniejszej do najnowszej):" << endl;
    cout << a.zwroc(0) << endl;
    cout << a.zwroc(1) << endl; 
    cout << a.zwroc(2) << endl;
    cout << "aktualna wartosc: " << a << endl;

    cout << endl <<"sprawdzamy przywracanie poprzednich wartosci:" << endl;

    a.przywroc(1); // powinno zamienic aktualna wartosc na 1 i zaktualizowac historie
    cout << "aktualna wartosc to " << a << endl;
    cout << "Zaktualizowana historia:" << endl;
    cout << a.zwroc(0) << endl;
    cout << a.zwroc(1) << endl; 
    cout << a.zwroc(2) << endl;

    cout << "sprawdzamy konstruktor kopiujacy:"<< endl;
    liczba b = a;

    cout << "wartosc b to " << b << endl;
    cout << "historia b:" << endl;
    cout << b.zwroc(0) << endl;
    cout << b.zwroc(1) << endl; 
    cout << b.zwroc(2) << endl;

    cout << "konstruktor przenoszacy:" << endl;
    liczba c(move(b));
    cout << "wartosc c: " << c << endl;
    cout << "historia c:" << endl;
    cout << c.zwroc(0) << endl;
    cout << c.zwroc(1) << endl; 
    cout << c.zwroc(2) << endl;
    cout << "a wartosc b to: " << b << endl;


    return 0;
}