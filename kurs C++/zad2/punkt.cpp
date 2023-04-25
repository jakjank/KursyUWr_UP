#include "punkt.hpp"
#include "wektor.hpp"
#include <math.h>
#include <iostream>
using namespace std;

punkt::punkt(){
    x = 0; y = 0;
}

punkt::punkt(double a ,double b){
    x = a; y = b;
}

void punkt::przesun(wektor w){
    x += w.wsp_x();
    y += w.wsp_y();
}

double punkt::wsp_x(){
    return x;
}

double punkt::wsp_y(){
    return y;
}

void punkt::obrot(punkt p , double alfa){
    double tmp_x = x - p.x;
    double tmp_y = y - p.y;
    
    x = round(((tmp_x * cos(alfa) - tmp_y * sin(alfa)) + p.x)*1000)/1000;
    y = round(((tmp_x * sin(alfa) + tmp_y * cos(alfa)) + p.y)*1000)/1000;
}

void punkt::symetria(punkt p){
    double odl_x = x - p.x;
    double odl_y = y - p.y;

    x += 2 * odl_x;
    y += 2 * odl_y;
}

void punkt::symetria_x(){
    y = -y;
}

void punkt::symetria_y(){
    x = -x;
}

ostream & operator<< (ostream &os, punkt p){
    return os << "(" << p.wsp_x() << ", " << p.wsp_y()<<")";
}