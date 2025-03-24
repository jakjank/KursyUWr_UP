#include <iostream>
#include "kolor.hpp"
#include "kolortransparentny.hpp"
#include "kolornazwany.hpp"
#include "kolornt.hpp"
#include "piksel.hpp"
#include "pikselkolorowy.hpp"

using namespace std;

int main()
{   
    cout<<"KOLOR"<<endl;
    kolor a = kolor(); // konstr. domyslny
    kolor b = kolor(20,30,40); // konstr. z wartosciami 
    kolor c = kolor::srednia(a, b);
    cout << "kolor a: "       << a << endl;
    cout << "kolor b: "       << b << endl;
    cout << "srednia a i b: " << c << endl;
 
    cout<<endl<<"KOLOR TRANSPARENTNY"<<endl;
    kolortransparentny x = kolortransparentny(90, 80, 70, 125);
    cout << "alfa "                   << x.get_alfa() << endl;
    cout << "x przed pociemnieniem: " << x            << endl;
    x.pociemnij();
    cout << "x po pociemnieniu: "     << x            << endl;

    cout<<endl<<"KOLOR NAZWANY"<<endl;
    kolornazwany y = kolornazwany(50,50,70,"kolorek");
    cout << "y: "       << y            << endl;
    cout << "nazwa y: " << y.get_name() << endl;
    y.rozjasnij();
    cout << "y po rozjasnieniu: " << y  << endl;

    cout<<endl<<"KOLOR NT"<<endl;
    kolornt z = kolornt(100,110,120, 255, "innykolorek");
    cout << "z: "    << z            << endl
         << "alfa: " << z.get_alfa() << endl
         << "nazwa: "<< z.get_name() << endl;

    cout<<endl<<"PIKSEL"<<endl;
    piksel p = piksel(1500, 1000);
    cout << "piksel p: "   << p         << endl;
    cout << "odl. gora: "  << p.gora()  << endl;
    cout << "odl. prawa: " << p.prawa() << endl;
    cout << "odl. dol: "   << p.dol()   << endl;
    cout << "odl. lewa: "  << p.lewa()  << endl;

    cout<<endl<<"PIKSEL KOLOROWY"<<endl;
    pikselkolorowy p2 = pikselkolorowy(920, 90, x);
    cout << "p2 przed przsunieciem " << p2 << endl;
    p2.przesun(-20,30);
    cout << "p2 po przesunieciu "    << p2 << endl;
    cout << "odleglosc p od p2 "     << odleglosc(p,p2);


    return 0;
}