#include <bits/stdc++.h>
#include "f_glob.hpp"
#include "punkt.hpp"
#include "odcinek.hpp"
#include "wektor.hpp"
#include "prosta.hpp"
#include "trojkat.hpp"
using namespace std;

double odleglosc (punkt a , punkt b){
    return sqrt((a.wsp_x() - b.wsp_x())*(a.wsp_x() - b.wsp_x()) +
                (a.wsp_x() - b.wsp_x())*(a.wsp_x() - b.wsp_x()) );
}


bool czy_rownolegle(odcinek a , odcinek b){
    double p1x = a.wsp_pocz().wsp_x(), 
           p1y = a.wsp_pocz().wsp_y(),
           k1x = a.wsp_kon().wsp_x() ,
           k1y = a.wsp_kon().wsp_y() ,
           p2x = b.wsp_pocz().wsp_x(), 
           p2y = b.wsp_pocz().wsp_y(),
           k2x = b.wsp_kon().wsp_x() ,
           k2y = b.wsp_kon().wsp_y() ;

    if( k1x - p1x == k2x - p2x && k1y - p1y == k2y - p2y){
        return true;
    }
    return false;
}

bool czy_prostopadle(odcinek a , odcinek b){
    double p1x = a.wsp_pocz().wsp_x(), 
           p1y = a.wsp_pocz().wsp_y(),
           k1x = a.wsp_kon().wsp_x() ,
           k1y = a.wsp_kon().wsp_y() ,
           p2x = b.wsp_pocz().wsp_x(), 
           p2y = b.wsp_pocz().wsp_y(),
           k2x = b.wsp_kon().wsp_x() ,
           k2y = b.wsp_kon().wsp_y() ;

    double il_skalar = (k1x - p1x) * (k2x - p2x) + 
                       (k1y - p1y) * (k2y - p2y);

    if(il_skalar == 0){
        return true;
    }
    return false;
}

double min(double x , double y){
    if(x < y){
        return x;
    }
    return y;
}
double max(double x , double y){
    if(x > y){
        return x;
    }
    return y;
}

bool rozlacznosc(trojkat t1 , trojkat t2){
    if (t1.czy_wew(t2.w_a()) || 
        t1.czy_wew(t2.w_b()) || 
        t1.czy_wew(t2.w_c())){
        return false;
    }
    if (t2.czy_wew(t1.w_a()) || 
        t2.czy_wew(t1.w_b()) ||
        t2.czy_wew(t1.w_c())){
        return false;
    }
    return true;
}

bool zawieranie(trojkat t1 , trojkat t2){
    if (t1.czy_wew(t2.w_a()) &&
        t1.czy_wew(t2.w_b()) && 
        t1.czy_wew(t2.w_c())){
        return true;
    }
    if (t2.czy_wew(t1.w_a()) && 
        t2.czy_wew(t1.w_b()) && 
        t2.czy_wew(t1.w_c())){
        return true;
    }
    return false;  
}