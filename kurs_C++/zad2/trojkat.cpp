#include "punkt.hpp"
#include "wektor.hpp"
#include "prosta.hpp"
#include <math.h>
#include "trojkat.hpp"
#include "odcinek.hpp"
#include <stdexcept>
#include <bits/stdc++.h>
using namespace std;

trojkat::trojkat(punkt w1, punkt w2, punkt w3){
    try{
        double ab = abs(sqrt((w2.wsp_x() - w1.wsp_x())*(w2.wsp_x() - w1.wsp_x()) + 
                             (w2.wsp_y() - w1.wsp_y())*(w2.wsp_y() - w1.wsp_y())));
        double ac = abs(sqrt((w3.wsp_x() - w1.wsp_x())*(w3.wsp_x() - w1.wsp_x()) + 
                             (w3.wsp_y() - w1.wsp_y())*(w3.wsp_y() - w1.wsp_y())));
        double cb = abs(sqrt((w2.wsp_x() - w3.wsp_x())*(w2.wsp_x() - w3.wsp_x()) + 
                             (w2.wsp_y() - w3.wsp_y())*(w2.wsp_y() - w3.wsp_y())));
        double x = (ab + ac + cb)/2;

        if (round(sqrt(x * (x-ab) * (x-cb) * (x-ac))*10)/10 == 0){
            throw invalid_argument("");
            //liczymy pole
        }                
    }
    catch(invalid_argument){
        clog << "punkty tworzace trojkat nie moga byc wspoliniowe" << endl;
    }
    a = w1;
    b = w2;
    c = w3;
}

void trojkat::przesun(wektor w){
    a.przesun(w);
    a.przesun(w);
    b.przesun(w);
}

void trojkat::obrot(punkt p, double alfa){
    a.obrot(p, alfa);
    b.obrot(p, alfa);
    c.obrot(p, alfa);
}

void trojkat::symetria(punkt p){
    a.symetria(p);
    b.symetria(p);
    c.symetria(p);
}

void trojkat::symetria_x(){
    a.symetria_x();
    b.symetria_x();
    c.symetria_x();
}

void trojkat::symetria_y(){
    a.symetria_y();
    b.symetria_y();
    c.symetria_y();
}

double trojkat::obwod(){
    double ab = abs(sqrt((b.wsp_x() - a.wsp_x())*(b.wsp_x() - a.wsp_x()) + 
                         (b.wsp_y() - a.wsp_y())*(b.wsp_y() - a.wsp_y())));
    double ac = abs(sqrt((c.wsp_x() - a.wsp_x())*(c.wsp_x() - a.wsp_x()) + 
                         (c.wsp_y() - a.wsp_y())*(c.wsp_y() - a.wsp_y())));
    double cb = abs(sqrt((b.wsp_x() - c.wsp_x())*(b.wsp_x() - c.wsp_x()) + 
                         (b.wsp_y() - c.wsp_y())*(b.wsp_y() - c.wsp_y())));
    return ab + ac + cb;
}

double trojkat::pole(){
    double ab = abs(sqrt((b.wsp_x() - a.wsp_x())*(b.wsp_x() - a.wsp_x()) + 
                         (b.wsp_y() - a.wsp_y())*(b.wsp_y() - a.wsp_y())));
    double ac = abs(sqrt((c.wsp_x() - a.wsp_x())*(c.wsp_x() - a.wsp_x()) + 
                         (c.wsp_y() - a.wsp_y())*(c.wsp_y() - a.wsp_y())));
    double cb = abs(sqrt((b.wsp_x() - c.wsp_x())*(b.wsp_x() - c.wsp_x()) + 
                         (b.wsp_y() - c.wsp_y())*(b.wsp_y() - c.wsp_y())));
    double x = (ab + ac + cb)/2;
    
    return round(sqrt(x * (x-ab) * (x-cb) * (x-ac))*10)/10;

}

bool trojkat::czy_wew(punkt p){
    double ab = abs(sqrt((b.wsp_x() - a.wsp_x())*(b.wsp_x() - a.wsp_x()) + 
                         (b.wsp_y() - a.wsp_y())*(b.wsp_y() - a.wsp_y())));
    double ac = abs(sqrt((c.wsp_x() - a.wsp_x())*(c.wsp_x() - a.wsp_x()) + 
                         (c.wsp_y() - a.wsp_y())*(c.wsp_y() - a.wsp_y())));
    double cb = abs(sqrt((b.wsp_x() - c.wsp_x())*(b.wsp_x() - c.wsp_x()) + 
                         (b.wsp_y() - c.wsp_y())*(b.wsp_y() - c.wsp_y())));
    double pa = abs(sqrt((p.wsp_x() - a.wsp_x())*(p.wsp_x() - a.wsp_x()) + 
                         (p.wsp_y() - a.wsp_y())*(p.wsp_y() - a.wsp_y())));
    double pb = abs(sqrt((b.wsp_x() - p.wsp_x())*(b.wsp_x() - p.wsp_x()) + 
                         (b.wsp_y() - p.wsp_y())*(b.wsp_y() - p.wsp_y())));
    double pc = abs(sqrt((p.wsp_x() - c.wsp_x())*(p.wsp_x() - c.wsp_x()) + 
                         (p.wsp_y() - c.wsp_y())*(p.wsp_y() - c.wsp_y())));

    double x = (ab + ac + cb)/2;
    double x1 = (pa + pb + ab)/2;
    double x2 = (pa + pc + ac)/2;
    double x3 = (pb + pc + cb)/2;

    double pole = round(sqrt(x * (x-ab) * (x-cb) * (x-ac))*10)/10;
    double pole1 = round(sqrt(x1 * (x1-ab) * (x1-pa) * (x1-pb))*10)/10;
    double pole2 = round(sqrt(x2 * (x2-pa) * (x2-pc) * (x2-ac))*10)/10;
    double pole3 = round(sqrt(x3 * (x3-pb) * (x3-pc) * (x3-cb))*10)/10;
    
    if(pole == pole1 + pole2 + pole3){
        return true;
    }
    return false;
}

punkt trojkat::w_a(){
    return a;
}
punkt trojkat::w_b(){
    return b;
}
punkt trojkat::w_c(){
    return c;
}

ostream & operator<< (ostream &os, trojkat t){
    return os << "[" << t.w_a() << ", " 
                     << t.w_b() << ", "
                     << t.w_c() << "]";
}