#include <iostream>
#include "punkt.hpp"
#include "wektor.hpp"
#include "prosta.hpp"
#include "odcinek.hpp"
#include "trojkat.hpp"
#include "f_glob.hpp"
using namespace std;

const double PI = 3.14159265359; 

int main(){
    //tworzenie punktow
    punkt o = punkt(0 , 0);
    punkt x = punkt(4 , -2);
    punkt y = punkt(-1.5 , 3);
    cout<<o<<endl;
    cout<<x<<endl;
    cout<<y<<endl;

    //tworzenie odcinkow
    odcinek xy = odcinek(x,y);
    cout<<xy<<endl;
    odcinek xx = odcinek(x,x); //mowi o bledzie
    cout<<xx<<endl;

    //tworzenie trojkatow
    trojkat xxx = trojkat(x,x,x); //mowi o bledzie
    trojkat tmp = trojkat(punkt(1,0), punkt(1,2), punkt(1,4)); //tez
    trojkat oxy = trojkat(o,x,y);
    cout<<oxy<<endl<<endl;

    //--------------------FUNKCJE PUNKTY
    cout<<"x przed obrotem o 360 "<<x<<endl;
    x.obrot(o , 2*PI);
    cout<<"x po obrocie 360 "<<x<<endl;
    cout<<"o przed obrotem o 90 "<<o<<endl;
    o.obrot(y , PI);
    cout<<"o po obrocie o 90 "<<o<<endl;
    cout<<"i z powrtem o -90";
    o.obrot(y , -PI);
    cout<<o<<endl<<endl;

    //translacja o wektor [1 ,-2]
    cout<<x<< "-> [1 , -2]-> ";
    x.przesun(wektor(1,-2));
    cout<<x<<endl<<endl;

    //symetria x wzg. (0,0)
    x.symetria(o);
    cout<<x<<endl;
    //symetria wzgl. OX
    x.symetria_x();
    cout<<x<<endl;
    //symetria wzgl. OY
    x.symetria_y();
    cout<<x<<endl<<endl;

    //odleglosc
    cout<<"odleglosc miedzy x i (0,0) = "<<odleglosc(x, o)<<endl<<endl;

    //f-------------------FUNKCJE ODCINKI
    cout<<"xy = "<<xy<<endl;
    odcinek ab = odcinek (punkt(1,2),punkt(-1,2));
    cout<<"ab = "<<ab<<endl;
    
    //dlugosc odcinka
    cout<<"dlugosc xy to "<< xy.dlugosc()<<" a dl. ab to "<<ab.dlugosc()<<endl;

    //czy rownolegle
    cout<<"czy ab i xy rownolegle? "<<czy_rownolegle(ab,xy)<<endl;
    cout<<"a czy ab i [(7,2)(9,2)] sa rownlegle? "<<czy_rownolegle(ab , odcinek(punkt(7,2),punkt(9,2)))<<endl;

    //czy prostpadle
    cout<<"czy ab i xy sa prostopadle? "<<czy_prostopadle(ab,xy)<<endl;
    cout<<"a czy ab i [(3,6),(3,-10)] sa prostopadle? "<<czy_prostopadle(ab,odcinek(punkt(3,6),punkt(3,-10)))<<endl<<endl;

    //-------------FUNKCJE TROJKATY
    trojkat t1 = oxy;
    trojkat t2 = trojkat(punkt(0,0), punkt(3,0), punkt(3,2));
    cout<<"trojkat t1 to "<<t1<<", t2 to "<<t2<<endl;

    //pole 
    cout<<"pole t1 to "<<t1.pole()<<endl;
    cout<<"pole t2 to "<<t2.pole()<<endl;

    //obwod
    cout<<"obwod t1 to "<<t1.obwod()<<endl;
    cout<<"obwod t2 to "<<t2.obwod()<<endl;

    //zawieranie punktu
    cout<<"czy (2.90 , 1) nalezy do t2? "<<t2.czy_wew(punkt(1.5,0))<<endl; //problem 
    cout<<"a czy (5,1) nalezy do t2? "<<t2.czy_wew(punkt(5,1))<<endl;

    //rozlacznosc
    cout<<"czy t1 i t2 sa rozlaczne? "<<rozlacznosc(t1, t2)<<endl;
    trojkat tmp2 = trojkat(punkt(-2,3), punkt(-4,20), punkt(-1,13));
    cout<<"a czy t2 i trojkat((-2,3), (-4,20), (-1,13)) sa rozlaczne.? "
        <<rozlacznosc(t2,tmp2)<<endl;

    //zawieranie
    cout<<"czy t1 jest w t2 lub t2 w t1? "<<zawieranie(t1, t2)<<endl;
    trojkat wielki = trojkat(punkt(0,0), punkt(4,-1), punkt(5,10));
    cout<<wielki;
    cout<<" czy w tym jest t2? "<<zawieranie(wielki, t2);

    return 0;
}
