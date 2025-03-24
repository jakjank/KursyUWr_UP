#include "punkt.hpp"
#include "wektor.hpp"
#include "prosta.hpp"
#include <math.h>
#include <algorithm>
#include "odcinek.hpp"
#include <stdexcept>
#include <iostream>
using namespace std;

odcinek::odcinek (punkt a , punkt b){
    try{
        if(a.wsp_x() == b.wsp_x() && a.wsp_y() == b.wsp_y()){
            throw invalid_argument("");
        }
    }
    catch(invalid_argument){
        clog << ("odcinek nie moze miec dlugosci 0") << endl;
    }
    poczatek = a;
    koniec = b;

}

void odcinek::przesun (wektor w){
    poczatek.przesun(w);
    koniec.przesun(w);
}

void odcinek::obrot (punkt p , double alfa){
    poczatek.obrot(p , alfa);
    koniec.obrot(p , alfa);
}

void odcinek::symetria (punkt p){
    poczatek.symetria(p);
    koniec.symetria(p);
}

void odcinek::symetria_x (){
    poczatek.symetria_x();
    koniec.symetria_x();
}

void odcinek::symetria_y (){
    poczatek.symetria_y();
    koniec.symetria_y();
}

double odcinek::dlugosc(){
    return sqrt(((poczatek.wsp_x() - koniec.wsp_x()) *
                 (poczatek.wsp_x() - koniec.wsp_x())) +
                ((poczatek.wsp_y() - koniec.wsp_y()) *
                 (poczatek.wsp_y() - koniec.wsp_y())));
}

bool odcinek::czy_nalezy(punkt p){

    //swietny wzorek z internetu
    double tmp = poczatek.wsp_x() * koniec.wsp_y() + 
                 koniec.wsp_x() * p.wsp_y() +
                 p.wsp_x() * poczatek.wsp_y() -
                 koniec.wsp_x() * poczatek.wsp_y() -
                 poczatek.wsp_x() * p.wsp_y() -
                 p.wsp_x() * koniec.wsp_y();

    if(tmp != 0){
        return false;
    }
    if ((min(poczatek.wsp_x() , koniec.wsp_x()) <= p.wsp_x()) &&
        (p.wsp_x() <= max(poczatek.wsp_x() , koniec.wsp_x())) &&
        (min(poczatek.wsp_y() , koniec.wsp_y()) <= p.wsp_y()) &&
        (p.wsp_y() <= max(poczatek.wsp_y() , koniec.wsp_y()))){
            return true;
        }
    return false;
}   

punkt odcinek::wsp_pocz(){
    return poczatek;
}

punkt odcinek::wsp_kon(){
    return koniec;
}

ostream & operator<< (ostream &os, odcinek l){
    return os << "[" <<l.wsp_pocz() << ", " << l.wsp_kon() << "]";
}