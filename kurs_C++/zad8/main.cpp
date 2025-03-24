#include "wymierna.hpp"
using namespace std;
using namespace obliczenia;

int main()
{
    Wymierna a(5,4);
    Wymierna b(3,5);
    Wymierna c(7,9);
    cout<< endl << "Tworzenie i wypisywanie ulamkow:" << endl;
    cout<< "(5/4) = a = " << a << endl;
    cout<< "(3/5) = b = " << b << endl;
    cout<< "(7/9) = c = " << c << endl;

    cout<< endl << "Test operacji arytmetycznych:" << endl;
    cout<< "a + b = " << a + b << endl;
    cout<< "a - c = " << a - c << endl;
    cout<< "a * b = " << a * b << endl;
    cout<< "a / c = " << a / c << endl;

    cout<< endl << "Test odwrotnosci i l. przeciwnej:" << endl;
    cout<< "!a = " << !a << endl;
    cout<< "-c = " << -c << endl;

    cout<< endl << "Test operatorow z przypisaniem:" <<endl;
    cout<< "a *= b : a = ";
    a *= b;
    cout<< a << endl;

    cout<< "a /= b : a = ";
    a /= b;
    cout<< a << endl;

    cout<< "a += c : a = ";
    a += c;
    cout<< a << endl;

    cout<< "a -= c : a = ";
    a -= c;
    cout<< a << endl;

    cout<< endl << "Test rzutowania:" << endl;
    cout<< "(int)a = "    << (int)a    <<endl;
    cout<< "(double)c = " << (double)c << endl;

}